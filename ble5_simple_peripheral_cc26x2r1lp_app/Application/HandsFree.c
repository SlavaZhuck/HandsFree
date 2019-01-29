/*
 * HandsFree.c
 *
 *  Created on: 24 џэт. 2019 у.
 *      Author: CIT_007
 */
#include "HandsFree.h"
#include "Noise_TRSH.h"
#include "Uart_commands.h"
#include "max9860_i2c.h"


/* Timer variables ***************************************************/
GPTimerCC26XX_Params tim_params;
GPTimerCC26XX_Handle blink_tim_hdl = NULL;
GPTimerCC26XX_Handle samp_tim_hdl = NULL;
GPTimerCC26XX_Value load_val[2] = {LOW_STATE_TIME, HIGH_STATE_TIME};
/*********************************************************************/

/* I2C variables *****************************************************/
static uint16_t i2c_read_delay;
/*********************************************************************/
int stream_on = 0;

extern PIN_Handle buttonPinHandle;
extern PIN_Handle ledPinHandle;

uint16_t counter_packet_send = 0;
uint16_t counter_packet_received = 0;
float packet_lost = 0;

void start_voice_handle(void)
{
    stream_on = 1;
    PIN_setOutputValue(ledPinHandle, Board_PIN_GLED, 1);
    GPTimerCC26XX_start(samp_tim_hdl);
}


void stop_voice_handle(void)
{
    GPTimerCC26XX_stop(samp_tim_hdl);
    stream_on = 0;
}


void HandsFree_init (void)
{
    max9860_I2C_Init();
    max9860_I2C_Read_Status();
    GPTimerCC26XX_Params_init(&tim_params);
    tim_params.width = GPT_CONFIG_32BIT;
    tim_params.mode = GPT_MODE_PERIODIC_UP;
    tim_params.debugStallMode = GPTimerCC26XX_DEBUG_STALL_ON;
    blink_tim_hdl = GPTimerCC26XX_open(Board_GPTIMER2A, &tim_params);

    if (blink_tim_hdl == NULL) {
        while (1);
    }
    GPTimerCC26XX_setLoadValue(blink_tim_hdl, (GPTimerCC26XX_Value)LOW_STATE_TIME);
    GPTimerCC26XX_registerInterrupt(blink_tim_hdl, blink_timer_callback, GPT_INT_TIMEOUT);
    GPTimerCC26XX_start(blink_tim_hdl);

    tim_params.width = GPT_CONFIG_16BIT;
    samp_tim_hdl = GPTimerCC26XX_open(Board_GPTIMER3A, &tim_params);
    if (samp_tim_hdl == NULL) {
        while (1);
    }
    GPTimerCC26XX_setLoadValue(samp_tim_hdl, (GPTimerCC26XX_Value)SAMP_TIME);
    GPTimerCC26XX_registerInterrupt(samp_tim_hdl, samp_timer_callback, GPT_INT_TIMEOUT);
}

void blink_timer_callback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask)
{
    static bool blink = false;
    if(blink)
    {
        blink = false;
        GPTimerCC26XX_setLoadValue(blink_tim_hdl, load_val[0]);

        PIN_setOutputValue(ledPinHandle, Board_PIN_RLED, 0);

        if(!stream_on)
        {
            PIN_setOutputValue(ledPinHandle, Board_PIN_GLED, 0);
        }
    }
    else
    {
        blink = true;
        GPTimerCC26XX_setLoadValue(blink_tim_hdl, load_val[1]);

         if(!stream_on)
        {
            PIN_setOutputValue(ledPinHandle, Board_PIN_GLED, 1);
        }
    }
}

void samp_timer_callback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask)
{

    if(stream_on)
    {
        ProjectZero_enqueueMsg(PZ_SEND_PACKET, NULL);
    }
}

void task_Handler (pzMsg_t *pMsg)
{
    // Cast to pzCharacteristicData_t* here since it's a common message pdu type.
    pzCharacteristicData_t *pCharData = (pzCharacteristicData_t *)pMsg->pData;

    switch(pMsg->event)
    {
    case PZ_SERVICE_WRITE_EVT: /* Message about received value write */
            /* Call different handler per service */
            switch(pCharData->svcUUID)
            {
    //            case LED_SERVICE_SERV_UUID:
    //                ProjectZero_LedService_ValueChangeHandler(pCharData);
    //                break;
              case DATA_SERVICE_SERV_UUID:
                  ProjectZero_DataService_ValueChangeHandler(pCharData);
                  break;
            }
            break;

        case PZ_SERVICE_CFG_EVT: /* Message about received CCCD write */
            /* Call different handler per service */
            switch(pCharData->svcUUID)
            {
    //            case BUTTON_SERVICE_SERV_UUID:
    //                ProjectZero_ButtonService_CfgChangeHandler(pCharData);
    //                break;
              case DATA_SERVICE_SERV_UUID:
                  ProjectZero_DataService_CfgChangeHandler(pCharData);
                  break;
            }
            break;
        case PZ_SEND_PACKET:
            uint8_t send_array[DS_STREAM_OUTPUT_LEN] = {(uint8_t)counter_packet_send};
            DataService_SetParameter(DS_STREAM_OUTPUT_ID, DS_STREAM_OUTPUT_LEN, send_array);
            counter_packet_send++;
            break;
        case PZ_I2C_Read_status:
            max9860_I2C_Read_Status();
            break;


        default:
            break;
      }

}


/*
 * @brief   Handle a CCCD (configuration change) write received from a peer
 *          device. This tells us whether the peer device wants us to send
 *          Notifications or Indications.
 *
 * @param   pCharData  pointer to malloc'd char write data
 *
 * @return  None.
 */
void ProjectZero_DataService_CfgChangeHandler(pzCharacteristicData_t *pCharData)
{
    // Cast received data to uint16, as that's the format for CCCD writes.
    uint16_t configValue = *(uint16_t *)pCharData->data;

    switch(pCharData->paramID)
    {
    case DS_STREAM_OUTPUT_ID:

        if (configValue) // 0x0001 and 0x0002 both indicate turned on.
        {
            if(stream_on != 1)
            {
                //GAPRole_SendUpdateParam(8, 8, 0, TIMEOUT, GAPROLE_RESEND_PARAM_UPDATE);
                start_voice_handle();
            }
        }
        else
        {
            stop_voice_handle();
        }
        break;
    }
}

/*
 * @brief   Handle a write request sent from a peer device.
 *
 *          Invoked by the Task based on a message received from a callback.
 *
 *          When we get here, the request has already been accepted by the
 *          service and is valid from a BLE protocol perspective as well as
 *          having the correct length as defined in the service implementation.
 *
 * @param   pCharData  pointer to malloc'd char write data
 *
 * @return  None.
 */
void ProjectZero_DataService_ValueChangeHandler(
    pzCharacteristicData_t *pCharData)
{
    // Value to hold the received string for printing via Log, as Log printouts
    // happen in the Idle task, and so need to refer to a global/static variable.
    static uint8_t received_string[DS_STREAM_START_LEN] = {0};

    switch(pCharData->paramID)
    {
    case DS_STREAM_START_ID:
        // Do something useful with pCharData->data here
        // -------------------------
        // Copy received data to holder array, ensuring NULL termination.
        memset(received_string, 0, DS_STREAM_START_LEN);
        memcpy(received_string, pCharData->data,
               MIN(pCharData->dataLen, DS_STREAM_START_LEN - 1));

        break;

    case DS_STREAM_INPUT_ID:

        counter_packet_received++;

        packet_lost = 100.0f * ((float)counter_packet_send - (float)counter_packet_received) / (float)counter_packet_send;
        // -------------------------
        // Do something useful with pCharData->data here
        break;

    default:
        return;
    }
}
