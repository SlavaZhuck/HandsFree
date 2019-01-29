/*
 * Uart_commands.h
 *
 *  Created on: 7 ����. 2018 �.
 *      Author: CIT_007
 */

#ifndef APPLICATION_UART_COMMANDS_H_
#define APPLICATION_UART_COMMANDS_H_

#include "Uart_parser.h"

void get_status(void);
uint8_t send_data(void);
void send_fh_param(void);
void send_fh_key(void);
void send_fh_cr_tp(void);

void get_fh_param(void);
void get_fh_key(void);
void get_fh_cr_tp(void);
void no_command(void);
void bad_crc(void);

void send_answer_for_command(uint8_t request);

//void status_ok(void);
//void status_bad(void);
//void rec_ok(void);
//void rec_error(void);
void no_command(void);

#endif /* APPLICATION_UART_COMMANDS_H_ */
