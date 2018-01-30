/*
 * Uart_Parser.h
 *
 *  Created on: 29 янв. 2018 г.
 *      Author: CIT_007
 */

#ifndef APPLICATION_UART_PARSER_H_
#define APPLICATION_UART_PARSER_H_

#include <stdint.h>

typedef struct {
    uint8_t header;

    uint8_t addr;

    uint8_t data_lenght ;
    uint8_t command;
    uint8_t data[256];
    uint16_t CRC;
} Serial_Rx_Data_Packet;



/*
  Name  : CRC-16 CCITT
  Poly  : 0x1021    x^16 + x^12 + x^5 + 1
  Init  : 0xFFFF
  Revert: false
  XorOut: 0x0000
  Check : 0x29B1 ("123456789")
  MaxLen: 4095 байт (32767 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/
unsigned short Crc16(unsigned char*pcBlock, unsigned short len);
 void OnRxByte(unsigned char Chr);
 void PackProcessing(void);
 void parser_init(void);
 void set_Myaddr(unsigned char addr);
 void set_Masteraddr(unsigned char addr);

#endif /* APPLICATION_UART_PARSER_H_ */
