/*
 * I2S_task.h
 *
 *  Created on: 9 дек. 2017 г.
 *      Author: HyperPC
 */

#ifndef I2S_I2S_TASK_H_
#define I2S_I2S_TASK_H_

#include "I2SCC26XX.h"
#include <ti/drivers/I2S.h>

/*********************************************************************
 * TYPEDEFS
 */
/*********************************************************************
 * TYPEDEFS
 */


#define AUDIO_DUPLEX_I2S_FRAME_EVENT                0x01
#define AUDIO_DUPLEX_I2S_ERROR_EVENT                0x02
#define AUDIO_DUPLEX_SEND_STOP_CMD_EVENT            0x04
#define AUDIO_DUPLEX_SEND_START_CMD_EVENT           0x08
#define AUDIO_DUPLEX_STOP_I2S_EVENT                 0x10
#define AUDIO_DUPLEX_START_I2S_EVENT                0x20
#define AUDIO_DUPLEX_CMD_STOP                       0x00
#define AUDIO_DUPLEX_CMD_START                      0x04
#define AUDIO_DUPLEX_CMD_START_MSBC                 0x05
#define AUDIO_DUPLEX_CMD_NONE                       0xFF

typedef void (*pfnAudioDuplexCB_t)(uint8_t events);
/*
* FUNCTIONS
 */
/*********************************************************************
 * @fn      SimpleBLEPeripheral_setEvent
 *
 * @brief   Function to set event in the Simple BLE Peripheral task.
 *
 * @param   None.
 *
 * @return  None.
 */
void SimpleBLEPeripheral_setEvent(uint8_t newEvents);
/*
 * Task creation function for the Simple BLE Peripheral.
 */
extern void I2S_createTask(void);
#endif /* I2S_I2S_TASK_H_ */
