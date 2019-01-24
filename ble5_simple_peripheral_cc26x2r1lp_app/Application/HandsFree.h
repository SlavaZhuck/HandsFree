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

void start_voice_handle(void);
void stop_voice_handle(void);

void HandsFree_init (void);

void task_Handler (pzMsg_t *pMsg);

#endif /* APPLICATION_HANDSFREE_H_ */
