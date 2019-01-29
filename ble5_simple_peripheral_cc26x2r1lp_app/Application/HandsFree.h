/*
 * HandsFree.h
 *
 *  Created on: 24 џэт. 2019 у.
 *      Author: CIT_007
 */

#ifndef APPLICATION_HANDSFREE_H_
#define APPLICATION_HANDSFREE_H_

#include "project_zero.h"
#include "./services/data_service.h"
#include <ti/drivers/timer/GPTimerCC26XX.h>

#define TMR_PERIOD                          48000000UL
#define LOW_STATE_TIME                      ((TMR_PERIOD / 10) * 9)
#define HIGH_STATE_TIME                     (TMR_PERIOD - LOW_STATE_TIME)
#define SAMP_TIME                         479999UL
//#define SAMP_TIME                          (4799999/4)


void start_voice_handle(void);
void stop_voice_handle(void);

void HandsFree_init (void);

void task_Handler (pzMsg_t *pMsg);

void blink_timer_callback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask);
void samp_timer_callback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask);


#endif /* APPLICATION_HANDSFREE_H_ */
