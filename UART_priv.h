/*
 * UART_priv.h
 *
 *  Created on: 3 Dec 2019
 *      Author: WEST
 */

#ifndef UART_PRIV_H_
#define UART_PRIV_H_

#include "UART_int.h"

#define UART0 0
#define UART1 1
#define UART2 2
#define UART4 4
#define UART5 5
#define UART6 6
#define UART7 7

#define PEN   1
#define EPS   2
#define STP2  3
#define FEN   4
#define WLEN  5
#define TXIM  5
#define RXIM  4


#define TXRIS 5
#define RXRIS 4

#define NORMAL_SPEED_MODE 0
#define DOUBLE_SPEED_MODE 1

#define MaxNumOFmodules 8

typedef struct
{
    u8 UART_NUM ;
    u16 BufferLength;
    u8 *ptrToBuffer ;
}BufferInfo;

typedef enum
{
    Available ,
    NotAvailable
}FIFO_StatusType;

typedef enum
{
    TxFIFO ,
    RxFIFO
}FIFO_Type;

UART_enumCheckType UART_PrivGetFIFOStatus (u8 copy_u8UARTnum, FIFO_Type copy_FIFO_TypeTx_Rx,FIFO_StatusType * StatusGetter );
void UART_privSendChar(u8 copy_u8UARTID ,u8 Data);
void UART_mainFunc (void);
void UART_vidBaudRateCalc(u8 i);
u8 UART_privGetConfigIndix(u8 copy_u8ID) ;
u8 UART_privRecieveChar(u8 copy_u8UARTID) ;


#define SYSCLOCK 0x00
#define PIOSC 0x5






#endif /* UART_PRIV_H_ */
