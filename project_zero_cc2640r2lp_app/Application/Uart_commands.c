/*
 * Uart_commands.c
 *
 *  Created on: 7 февр. 2018 г.
 *      Author: CIT_007
 */
#include <string.h>
#include "Uart_commands.h"
#include "project_zero.h"
#include "Uart_Parser.h"
#include <ti/drivers/UART.h>
#include "icall_ble_api.h"

#define KEY_SIZE                            16

 unsigned short calculated_CRC_TX;
extern Serial_Data_Packet Tx_Data;
extern Serial_Data_Packet Rx_Data;
extern UART_Handle uart;
extern uint8_t macAddress[6];

void calcCRC_andSend(void);
void clear_Tx_packet(void);

void calcCRC_andSend(void){
    calculated_CRC_TX = Crc16((unsigned char*)(&Tx_Data)+1,(unsigned short)(Tx_Data.data_lenght)+3);
    Tx_Data.CRC = calculated_CRC_TX;
    UART_writeCancel(uart);
    UART_write(uart, &Tx_Data, Tx_Data.data_lenght+4);
    UART_write(uart, &Tx_Data.CRC, 2);
}

void send_answer_for_command(uint8_t request){
    clear_Tx_packet();
    Tx_Data.data_lenght = 0;
    Tx_Data.command = request;
    calcCRC_andSend();
}


uint8_t send_data(void){//here we receive data from host

    //copying data somewhere
    return 1;
}


void send_fh_key (void){

    clear_Tx_packet();

    if(!write_aes_key(&Rx_Data.data)){
        send_answer_for_command(REC_OK);
    }else{
        send_answer_for_command(REC_ERROR) ;
    }
}

void send_fh_cr_tp(void){   //TODO
    clear_Tx_packet();
    if(1){
        send_answer_for_command(REC_OK);
    }else{
        send_answer_for_command(REC_ERROR) ;
    }
}

void get_fh_param(void){
    //readMacfunction TODO
    //hciStatus_t HCI_ReadBDADDRCmd

    clear_Tx_packet();
    Tx_Data.data_lenght = 6;//MAClenght
    for(uint8_t i = 0 ;i<Tx_Data.data_lenght;i++){
        Tx_Data.data[i]=macAddress[i];
    }
    Tx_Data.command = SEND_FH_PARAM ;
    calcCRC_andSend();
}

uint8_t read_key[KEY_SIZE];

void get_fh_key(void){

    clear_Tx_packet();

    if(!read_aes_key(&read_key)){
        Tx_Data.data_lenght = KEY_SIZE;
        for(uint8_t i = 0 ;i<KEY_SIZE;i++){
            Tx_Data.data[i]=read_key[i];
        }
        Tx_Data.command = SEND_FH_KEY ;
        calcCRC_andSend();
    }else{
        Tx_Data.command = REC_ERROR ;
        calcCRC_andSend();
    }
}

void get_fh_cr_tp(void){
    clear_Tx_packet();
    char type[7]= {'A', 'e', 's', '1', '2', '8' , '\0'};
    Tx_Data.data_lenght = 7;

    for(uint8_t i = 0 ;i<Tx_Data.data_lenght;i++){
        Tx_Data.data[i]=type[i];
    }
    Tx_Data.command = SEND_FH_CR_TP;
    calcCRC_andSend();
}


void no_command (void){
    clear_Tx_packet();
    Tx_Data.data_lenght = 0;
    Tx_Data.command = NO_COMAND;
    calcCRC_andSend();
}


void clear_Tx_packet(void){
    memset(&Tx_Data.data_lenght,0,sizeof(Tx_Data.data_lenght)+sizeof(Tx_Data.command)+sizeof(Tx_Data.data)+sizeof(Tx_Data.CRC));
}
