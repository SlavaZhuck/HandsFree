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
#include "I2C_task.h"
#include <ti/drivers/I2C.h>

#include <ti/drivers/PWM.h>
#include <ti/drivers/timer/GPTimerCC26XX.h>
#include <ti/drivers/crypto/CryptoCC26XX.h>
//#include <ti/drivers/pdm/PDMCC26XX.h>
//#include "PDMCC26XX.h"

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Mailbox.h>

#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Error.h>

// Task configuration
#define I2C_TASK_PRIORITY                     1

#ifndef I2C_TASK_STACK_SIZE
#define I2C_TASK_STACK_SIZE                   1300
#endif
// Task configuration
Task_Struct i2cTask;
Char i2cTaskStack[I2C_TASK_STACK_SIZE];
static void I2C_taskFxn(UArg a0, UArg a1);

void I2C_createTask(void)
{
  Task_Params taskParams;

  // Configure task
  Task_Params_init(&taskParams);
  taskParams.stack = i2cTaskStack;
  taskParams.stackSize = I2C_TASK_STACK_SIZE;
  taskParams.priority = I2C_TASK_PRIORITY;

  Task_construct(&i2cTask, I2C_taskFxn, &taskParams, NULL);
}

void delay_tick(uint32_t count){
    uint32_t counter = count;
    while(counter>0){
        counter--;
    }
}



static void I2C_taskFxn(UArg a0, UArg a1)
{
    unsigned int    i;
        uint16_t        temperature;
        uint8_t         i2cTxBuffer[15];
        uint8_t         i2cRxBuffer[18];
        I2C_Handle      i2c;
        I2C_Params      i2cParams;
        I2C_Transaction i2cTransaction;

        //GPIO_init();
        I2C_init();
        /* Create I2C for usage */
            I2C_Params_init(&i2cParams);
            //i2cParams.transferMode  = I2C_MODE_CALLBACK;
            i2cParams.bitRate = I2C_100kHz;
            i2c = I2C_open(Board_I2C0, &i2cParams);
            if (i2c == NULL) {
                Display_printf(display, 0, 0, "Error Initializing I2C\n");
                while (1);
            }
            else {
                Display_printf(display, 0, 0, "I2C Initialized!\n");
            }

            /* Point to the T ambient register and read its 2 bytes */
            i2cTxBuffer[0]  = 0x03;//!addr reg
            i2cTxBuffer[1]  = 0x10;//!system clock                       //clock control            0x03
            i2cTxBuffer[2]  = 0x80;//!stereo audio clock control high                               0x04
            i2cTxBuffer[3]  = 0x00;//!stereo audio clock control low                                0x05
            i2cTxBuffer[4]  = 0x00;//!interface                          //digital audio interface  0x06
            i2cTxBuffer[5]  = 0x02;//!interface                                                     0x07
            i2cTxBuffer[6]  = 0x00;//!voice filter                       //digital filtering        0x08
            i2cTxBuffer[7]  = 0x06;//!DAC att                            //digital level control    0x09
            i2cTxBuffer[8]  = 0x00;//!ADC output levels                                             0x0A
            i2cTxBuffer[9]  = 0x40;//!DAC gain and sidetone                                         0x0B
            i2cTxBuffer[10] = 0x00;//!microphone gain                    //MIC level control        0x0C
            i2cTxBuffer[11] = 0x00;                                     //RESERVED                  0x0D
            i2cTxBuffer[12] = 0x00;//!microphone AGC                   //MIC automatic gain control 0x0E
            i2cTxBuffer[13] = 0x00;//!Noise gate, mic AGC                                           0x0F
            i2cTxBuffer[14] = 0x88;//!System shutdown                    //POWER MANAGEMENT         0x10


            volatile static uint32_t delay = 10000;
            while(delay>0){
                delay--;
            }
            i2cTransaction.slaveAddress = 0x10;
            i2cTransaction.writeBuf = i2cTxBuffer;
            i2cTransaction.readBuf = i2cRxBuffer;//rxBuffer;

            i2cTransaction.writeCount = 15;
            i2cTransaction.readCount = 0;
            I2C_transfer(i2c, &i2cTransaction);
            //delay_tick(1000000);
            //i2cTransaction.writeCount = 0;
            //i2cTransaction.readCount = 18;
            //I2C_transfer(i2c, &i2cTransaction);
            //delay_tick(1000000);
            I2C_close(i2c);
            /* Take 20 samples and print them out onto the console */
            //for (;;) {
                //if(i2cTransaction.slaveAddress==1)
                //    i2cTransaction.slaveAddress = i2cTransaction.slaveAddress=0x80;
               // else
              //      i2cTransaction.slaveAddress = i2cTransaction.slaveAddress>>1;


           // }

}

