/*
 * HandsFree.c
 *
 *  Created on: 24 џэт. 2019 у.
 *      Author: CIT_007
 */
#include "HandsFree.h"

int stream_on = 0;


void start_voice_handle(void)
{
    stream_on = 1;
}


void stop_voice_handle(void)
{
    stream_on = 0;
}


void HandsFree_init (void)
{

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
        default:
            break;
      }

}
