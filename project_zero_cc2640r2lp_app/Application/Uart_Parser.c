/*
 * Uart_Parser.c
 *
 *  Created on: 29 €нв. 2018 г.
 *      Author: CIT_007
 */
#include <string.h>
#include "Uart_Parser.h"

#define SYNC_FRAME   0xAA

//enum State{ stHEADER = 0,
//            stAddr,
//            stDL,
//            stCtrl,
//            stDATA,
//            stCRC} uiState;
State uiState;
Serial_Rx_Data_Packet Rx_Data;
Serial_Rx_Data_Packet Tx_Data = {
                     .header = SYNC_FRAME,
                     .addr = 0x13,
                     .data_lenght = 0x01,
                     .command = 0x00,
                     .data[0] = 0xAB,
                     .CRC = 0xFF   };

unsigned char uiHeader;
uint16_t CRC16    ;       //начальное значение CRC
uint16_t ByteCntR ;       //ничего не прин€то
uint16_t ByteCntT ;       //ничего не отправлено
uint16_t NewPack  ;       //пакте не прин€т
unsigned char Address = (ADR_TX(ADR_LZO) | ADR_REC(ADR_PC))  ;       //addr
unsigned char current_data_lenght = 0x0  ;       //addr
unsigned short calculated_CRC = 0;

//void set_Myaddr(unsigned char addr){
//
//    Address&= 0xF0 | addr;
//
//}
//void set_Masteraddr(unsigned char addr){
//    Address&= (addr<<4) | 0x0F ;
//    //Address = ADR_TX(addr);
//}



void parser_init(void){
   // IUsartInterface::init(cfg, fnWriteBuf);
//    set_Myaddr(3);
//    set_Masteraddr(1);
   // CRC16       = 0xFFFF;       //начальное значение CRC
    ByteCntR    = 0;            //ничего не прин€то
    ByteCntT    = 0;            //ничего не отправлено
    NewPack     = 0;            //пакте не прин€т
    current_data_lenght = 0;
    memset(&Rx_Data,0,sizeof(Rx_Data));
    uiState = stHEADER;
    uiHeader = SYNC_FRAME;
    Rx_Data.addr = 0x13;
    calculated_CRC = 0;
  //  last_time = CSystemCore::getSysTick();

}

unsigned short Crc16(unsigned char*pcBlock, unsigned short len)
{
    unsigned short crc =0xFFFF;
    unsigned char i;

    while (len--){
        crc ^=*pcBlock++<<8;

        for (i =0; i <8; i++)
                crc = crc &0x8000? (crc <<1) ^0x1021: crc <<1;
        }
    return crc;
}

void OnRxByte( unsigned char Chr){
    switch (uiState){
         case stHEADER:{

          if(SYNC_FRAME == Chr && !NewPack){
              Rx_Data.header = Chr;

              uiState = stAddr;
           }

        break;}
        case stAddr:{
           // __byte((int*)(&(m_pcPacketRx.ucCmd)), ByteCntR++) = Chr;
            if(Chr == Rx_Data.addr)
             uiState = stDL;
        break;}

        case stDL:{
           // __byte((int*)(&(m_pcPacketRx.ucCmd)), ByteCntR++) = Chr;
            Rx_Data.data_lenght = Chr;
            uiState = stCtrl;
        break;}

        case stCtrl:{
           // __byte((int*)(&(m_pcPacketRx.ucCmd)), ByteCntR++) = Chr;
            Rx_Data.command = Chr;
            if(Rx_Data.data_lenght==0){
                uiState = stCRC;
            }else{
                uiState = stDATA;
            }

            ByteCntR = 0;
        break;}

        case stDATA:{
           // __byte((int*)(&(m_pcPacketRx.ucCmd)), ByteCntR++) = Chr;
            Rx_Data.data[ByteCntR] = Chr;
            ByteCntR++;
            if(ByteCntR == Rx_Data.data_lenght){
                Rx_Data.CRC = 0;
                uiState = stCRC;
                ByteCntR = 0;
            }
        break;}

        case stCRC:{
            if(ByteCntR==0){
                calculated_CRC = 0;
                Rx_Data.CRC = Chr<<8;
                ByteCntR++;
            }else if(1 == ByteCntR){
                Rx_Data.CRC |= Chr;
                calculated_CRC = Crc16((unsigned char*)(&Rx_Data)+1,(unsigned short)(Rx_Data.data_lenght)+3);
                // 2 bytes of CRC received
                uiState = stHEADER;

                if (calculated_CRC == Rx_Data.CRC){                               // Check for correct CRC
                    NewPack = 1;
                }else{
                    NewPack = 0;
                    memset(&Rx_Data.data_lenght,0,sizeof(Rx_Data.data_lenght)+sizeof(Rx_Data.command)+sizeof(Rx_Data.data)+sizeof(Rx_Data.CRC));
                }
                ByteCntR = 0x00;
            }

        break;}
        default:
        {
            ByteCntR = 0;
            uiState = stHEADER;
            break;
        }
    };
}

//extern UART_Handle uart;

uint16_t PackProcessing(void){
    if(!NewPack){


        return 0;         //Ќичего не делать
    }
//    statusRx.Word = m_pcPacketRx.ucCmd;
//    last_time = CSystemCore::getSysTick();


    // „топ не принимал новые данные пока не обработал старые, чистим этот флаг только в конце обработки
    NewPack = 0;
    return 1;// ”же пакета нет
}
