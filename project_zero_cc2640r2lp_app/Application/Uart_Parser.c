/*
 * Uart_Parser.c
 *
 *  Created on: 29 €нв. 2018 г.
 *      Author: CIT_007
 */
#include <string.h>
#include "Uart_Parser.h"
#include "Uart_commands.h"
#include "project_zero.h"

#define SYNC_FRAME   0xAA

//enum State{ stHEADER = 0,
//            stAddr,
//            stDL,
//            stCtrl,
//            stDATA,
//            stCRC} uiState;
State uiState;

Serial_Data_Packet Rx_Data;

Serial_Data_Packet Tx_Data = {
                     .header = SYNC_FRAME,
                     .addr = 0x13,
                     .data_lenght = 0x00,
                     .command = 0x00,
                     .data[0] = 0x00,
                     .CRC = 0xFF   };



unsigned char uiHeader;
uint16_t CRC16    ;       //начальное значение CRC
uint16_t ByteCntR ;       //ничего не прин€то
uint16_t ByteCntT ;       //ничего не отправлено
uint16_t NewPack  ;       //пакте не прин€т
unsigned char Address = (ADR_TX(ADR_LZO) | ADR_REC(ADR_PC))  ;       //addr
unsigned char current_data_lenght = 0x0  ;       //addr
unsigned short calculated_CRC = 0;
unsigned char uart_val = 1;
static unsigned char adc_val = 1;

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

//extern GPTimerCC26XX_Value system_tick;
//extern GPTimerCC26XX_Handle system_time;

void OnRxByte( unsigned char Chr){

    static GPTimerCC26XX_Value timestamp = 0;

//    if(GPTimerCC26XX_getValue(system_time)-timestamp > UART_BYTE_DELAY_TIME){
//        uiState = stHEADER;
//    }

    switch (uiState){
         case stHEADER:{

          if(SYNC_FRAME == Chr && !NewPack){
              Rx_Data.header = Chr;
             // GPTimerCC26XX_setLoadValue(system_time, 0);
             // timestamp = GPTimerCC26XX_getValue(system_time);
              uiState = stAddr;
           }

        break;}
        case stAddr:{
            if(Chr == Rx_Data.addr)
             uiState = stDL;
        break;}

        case stDL:{
            Rx_Data.data_lenght = Chr;
            uiState = stCtrl;
        break;}

        case stCtrl:{
            Rx_Data.command = Chr;
            if(Rx_Data.data_lenght==0){
                uiState = stCRC;
            }else{
                uiState = stDATA;
            }

            ByteCntR = 0;
        break;}

        case stDATA:{
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
                    bad_crc();
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



uint16_t PackProcessing(void){
    if(!NewPack){


        return 0;         //Ќичего не делать
    }
//    statusRx.Word = m_pcPacketRx.ucCmd;
//    last_time = CSystemCore::getSysTick();
    uint16_t receive_command = Rx_Data.command;
    switch(receive_command){

        case GET_STATUS:{//we should send our status

            if(1){
                send_answer_for_command(STATUS_OK);
            }else{
                send_answer_for_command(STATUS_BAD);
            }
        break;}

        case SEND_DATA :{//we receive data from host

            if(send_data()){
                send_answer_for_command(REC_OK);
            }else{
                send_answer_for_command(REC_ERROR) ;
            }

        break;}

        case SEND_FH_KEY :{//send encryption key
			user_enqueueRawAppMsg(APP_MSG_Write_key, &uart_val, 1);


        break;}

        case SEND_FH_CR_TP :{//send encription type

            send_fh_cr_tp();

        break;}

        case GET_FH_PARAM :{//get mac address
            user_enqueueRawAppMsg(APP_MSG_Read_ADC_Voltage, &adc_val, 1);
            get_fh_param();

        break;}

        case GET_FH_KEY :{//get encryption key
            user_enqueueRawAppMsg(APP_MSG_Read_key, &uart_val, 1);


        break;}

        case GET_FH_CR_TP :{//get encryption type

            get_fh_cr_tp();

        break;}

        default:{

            no_command();
        break;}

    }

    // „топ не принимал новые данные пока не обработал старые, чистим этот флаг только в конце обработки
    NewPack = 0;
    return 1;// ”же пакета нет
}
