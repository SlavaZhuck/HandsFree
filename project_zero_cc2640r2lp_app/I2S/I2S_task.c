/*
 * I2C_task.c
 *
 *  Created on: 9 дек. 2017 г.
 *      Author: HyperPC
 */
/*
 * INCLUDES
 */
#include <string.h>

//#define xdc_runtime_Log_DISABLE_ALL 1  // Add to disable logs from this file

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/drivers/PIN.h>
#include <ti/display/Display.h>
#include <driverlib/vims.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>

#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>
#ifdef UARTLOG_ENABLE
#  include "UartLog.h"
#endif

/* This Header file contains all BLE API and icall structure definition */
#include "icall_ble_api.h"
#include <icall.h>

#include <osal_snv.h>
#include <peripheral.h>
#include <devinfoservice.h>

#include "util.h"

#include "Board.h"
#include <I2S/I2S_task.h>
#include <driverlib/flash.h>
#include <ti/drivers/timer/GPTimerCC26XX.h>
#include <ti/drivers/crypto/CryptoCC26XX.h>
//#include <ti/drivers/pdm/PDMCC26XX.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Mailbox.h>

#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Error.h>
//#include "audio_duplex.h"

// Task configuration
#define I2S_TASK_PRIORITY                     1
#define I2S_SAMPLE_RATE           1024000
#define I2S_BLOCK_SIZE           128

#define AUDIO_DUPLEX_BUFSIZE_ADPCM                  96
#define AUDIO_DUPLEX_HDRSIZE_ADPCM                  4
#define AUDIO_DUPLEX_ADPCM_SAMPLES_PER_FRAME        AUDIO_DUPLEX_BUFSIZE_ADPCM


#ifndef I2S_TASK_STACK_SIZE
#define I2S_TASK_STACK_SIZE                   2048
#endif

// Display Interface



#include <driverlib/flash.h>
#include <math.h>

#define M_PI        3.14159265358979323846
#define I2S_SAMP_PER_FRAME    128

#define I2S_BUF     sizeof(int16_t) * (I2S_SAMP_PER_FRAME *   \
                                        I2SCC26XX_QUEUE_SIZE * 2)


#define I2S_MEM_BASE (GPRAM_BASE + FlashSectorSizeGet())
#define AUDIO_DUPLEX_STREAM_TYPE_NONE               AUDIO_DUPLEX_CMD_STOP
#define AUDIO_DUPLEX_STREAM_TYPE_ADPCM              AUDIO_DUPLEX_CMD_START
#define AUDIO_DUPLEX_STREAM_TYPE_MSBC               AUDIO_DUPLEX_CMD_START_MSBC
#define BLEAUDIO_MAX_NOTSIZE            100
#define AUDIO_DUPLEX_MAX_VOLUME                     75
#define BLEAUDIO_NUM_NOT_PER_FRAME_ADPCM  1
#define HCI_EXT_TX_POWER_5_DBM                         LL_EXT_TX_POWER_5_DBM  //!< 5 dBm
#define AUDIO_DUPLEX_MSBC_SAMPLES_PER_FRAME         120


static void AudioDuplex_disableCache();
//static uint8_t audioProfileAudio[BLEAUDIO_MAX_NOTSIZE];
static uint8_t audioProfileAudioSize = BLEAUDIO_MAX_NOTSIZE;
static I2SCC26XX_StreamNotification i2sStream;
static pfnAudioDuplexCB_t appAudioCB = NULL;
static void AudioDuplex_i2sCallbackFxn(I2SCC26XX_Handle handle,
                                        I2SCC26XX_StreamNotification *notification);



// Task configuration
Task_Struct I2STask;
Char I2STaskStack[I2S_TASK_STACK_SIZE];
static void I2S_taskFxn(UArg a0, UArg a1);

static I2SCC26XX_StreamNotification i2sStream;

static I2SCC26XX_Params i2sParams =
{
    .requestMode            = I2SCC26XX_CALLBACK_MODE,
    .ui32requestTimeout     = BIOS_WAIT_FOREVER,
    .callbackFxn            = AudioDuplex_i2sCallbackFxn,
    .blockSize              = AUDIO_DUPLEX_MSBC_SAMPLES_PER_FRAME,
    .pvContBuffer           = NULL,
    .ui32conBufTotalSize    = 0,
    .pvContMgtBuffer        = NULL,
    .ui32conMgtBufTotalSize = 0,
    .currentStream          = &i2sStream
};

static I2SCC26XX_Handle i2sHandle = NULL;
static int16_t *audio_decoded = NULL;
static uint8_t *i2sContMgtBuffer = NULL;
static bool i2sStreamInProgress = false;
Bool bufferReady = false;

void I2S_createTask(void)
{
  Task_Params taskParams;

  // Configure task
  Task_Params_init(&taskParams);
  taskParams.stack = I2STaskStack;
  taskParams.stackSize = I2S_TASK_STACK_SIZE;
  taskParams.priority = I2S_TASK_PRIORITY;

  Task_construct(&I2STask, I2S_taskFxn, &taskParams, NULL);
}

#define DATA_SIZE I2S_SAMP_PER_FRAME



void fill_data (int16_t *data[],int size);


static void I2S_taskFxn(UArg a0, UArg a1)
{
//////AudioDuplex_open
    //i2sHandle = (I2SCC26XX_Handle)&(I2SCC26XX_config);
    int16_t data0[DATA_SIZE];
    int16_t data1[DATA_SIZE];
    int16_t data2[DATA_SIZE];
    int16_t data3[DATA_SIZE];

    for(int16_t i = 0; i<DATA_SIZE;i++){
        data0[i]=(int16_t)(sin(i*M_PI/180.0*2.82/4)*8192.0);
        data1[i]=(int16_t)(sin(i*M_PI/180.0*2.82/4+M_PI/180.0*90)*8192.0);
        data2[i]=(int16_t)(sin(i*M_PI/180.0*2.82/4+M_PI/180.0*180)*8192.0);
        data3[i]=(int16_t)(sin(i*M_PI/180.0*2.82/4+M_PI/180.0*270)*8192.0);
    }
    I2SCC26XX_init(i2sHandle);

    I2SCC26XX_Handle i2sHandleTmp = NULL;
    AudioDuplex_disableCache();

    i2sContMgtBuffer = (uint8_t *)(I2S_MEM_BASE + I2S_BUF + 1);
    audio_decoded = (int16_t *)I2S_MEM_BASE;
    // Setup I2S Params
    i2sParams.blockSize              = I2S_SAMP_PER_FRAME;
    i2sParams.pvContBuffer           = (void *) audio_decoded;
    i2sParams.pvContMgtBuffer        = (void *) i2sContMgtBuffer;
    i2sParams.ui32conMgtBufTotalSize =  I2S_BLOCK_OVERHEAD_IN_BYTES *  \
                                        I2SCC26XX_QUEUE_SIZE\
                                        * 2;

    i2sParams.ui32conBufTotalSize    =  sizeof(int16_t) * (I2S_SAMP_PER_FRAME * \
                                        I2SCC26XX_QUEUE_SIZE \
                                        * 2);
    // Reset I2S handle and attempt to open
    i2sHandle = (I2SCC26XX_Handle)&(I2SCC26XX_config);
    i2sHandleTmp = I2SCC26XX_open(i2sHandle, &i2sParams);

//////AudioDuplex_eventHandler
    //////AUDIO_DUPLEX_START_I2S_EVENT
    //////i2sStreamInProgress
        I2SCC26XX_BufferRequest bufferRequest;
        I2SCC26XX_BufferRelease bufferRelease;
        bufferRequest.buffersRequested = I2SCC26XX_BUFFER_OUT;
        //bufferRequest.bufferOut = &data;
        //bufferRequest.bufferHandleOut = &data;

        i2sStreamInProgress = I2SCC26XX_startStream(i2sHandle);

    /*
        while (!bufferReady);
        bool gotBuffer = I2SCC26XX_requestBuffer(i2sHandle, &bufferRequest);

        bufferRelease.bufferHandleOut = bufferRequest.bufferHandleOut;
        bufferRelease.bufferHandleIn = NULL;
        I2SCC26XX_releaseBuffer(i2sHandle, &bufferRelease);

        I2SCC26XX_stopStream(i2sHandle);

        I2SCC26XX_close(i2sHandle);
    */

    for (;;)
    {
        bool gotBuffer = I2SCC26XX_requestBuffer(i2sHandle, &bufferRequest);
        if (gotBuffer)
        {
            //memset(bufferRequest.bufferOut, &data[0], 96);
            memcpy(bufferRequest.bufferOut, &data0[0], sizeof(data0));
            bufferRelease.bufferHandleOut = bufferRequest.bufferHandleOut;
            bufferRelease.bufferHandleIn = NULL;
            I2SCC26XX_releaseBuffer(i2sHandle, &bufferRelease);
        }
    }

    I2SCC26XX_stopStream(i2sHandle);

    I2SCC26XX_close(i2sHandle);

        // Send the buffer to the BoosterPack


//////AudioDuplex_startStreaming
    //i2sHandle = AudioDuplex_openI2S();
    //////AudioDuplex_openI2S




    for (;;){

    }
}







void I2S_callbackFxn(void){

}

/*********************************************************************
 * @fn      AudioDuplex_i2sCallbackFxn
 *
 * @brief   Callback functtion from I2S driver, sets events to be
 *          processed in the task context
 *
 * @param   None.
 *
 * @return  None.
 */
static void AudioDuplex_i2sCallbackFxn(I2SCC26XX_Handle handle,
                                        I2SCC26XX_StreamNotification *notification)
{
    bufferReady = true;
    if (notification->status == I2SCC26XX_STREAM_ERROR)
    {
        if(appAudioCB != NULL)
        {
            // Notify the Application of the event
            (*appAudioCB)(AUDIO_DUPLEX_I2S_ERROR_EVENT);
        }
    }
    else if (notification->status == I2SCC26XX_STREAM_BUFFER_READY)
    {
        if(appAudioCB != NULL)
        {
            // Notify the Application of the event
            (*appAudioCB)(AUDIO_DUPLEX_I2S_FRAME_EVENT);
        }
    }
    else if (notification->status == I2SCC26XX_STREAM_BUFFER_READY_BUT_NO_AVAILABLE_BUFFERS)
    {
        if(appAudioCB != NULL)
        {
            // Notify the Application of the event
            (*appAudioCB)(AUDIO_DUPLEX_I2S_FRAME_EVENT);
        }
    }
}
/*********************************************************************
 * @fn      AudioDuplex_disableCache
 *
 * @brief   Disables the instruction cache and sets power constaints
 *          This prevents the device from sleeping while streaming
 *
 * @param   None.
 *
 * @return  None.
 */
static void AudioDuplex_disableCache()
{
    uint_least16_t hwiKey = Hwi_disable();
    Power_setConstraint(PowerCC26XX_SB_VIMS_CACHE_RETAIN);
    Power_setConstraint(PowerCC26XX_NEED_FLASH_IN_IDLE);
    VIMSModeSafeSet(VIMS_BASE, VIMS_MODE_DISABLED, true);
    Hwi_restore(hwiKey);
}
