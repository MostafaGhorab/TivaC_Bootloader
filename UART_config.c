/*
 * UART_config.c
 *
 *  Created on: 3 Dec 2019
 *      Author: WEST
 */
#include "UART_priv.h"
#include "UART_int.h"
#include "UART_Config.h"

u8 G_UART_sendFinished =0;
u8 G_UART_RecFinished =0;
void UART_sendCallBacl (void)
{
    G_UART_sendFinished  =1;

}

void UART_RecCallBacl (void)
{
    G_UART_RecFinished  =1;

}
 UART_module UART_ConfigArray [NUMBER_OF_MODULES];

UART_module UART_ConfigArray [NUMBER_OF_MODULES] =

{
 {UART0 ,
  115200,
  UART_8BitData ,
  UART_ONEStopBit ,
  UART_FIFO_Enabled,
  UART_ParityBitDisabled ,
  UART_EvenParity ,
  { UART_2ByteTriggerLength,IDLE_State,INT_ENABLED,UART_sendCallBacl },
  { UART_2ByteTriggerLength,IDLE_State,INT_ENABLED,UART_RecCallBacl } ,
  NORMAL_SPEED_MODE   }

};


//extern void (*GPS_ptr)(void);
//
//extern void (*UART1_RX)(void);
//UART1_RX=&GPS_ptr;




