/*
 * UART_int.h
 *
 *  Created on: 3 Dec 2019
 *      Author: WEST
 */

#include "std_types.h"
#include "Port.h"
#ifndef UART_INT_H_
#define UART_INT_H_
typedef enum
{
    okay=0,
    nokay=1,
}UART_enumCheckType;

typedef enum
{
    UART_5BitData = 0,
    UART_6BitData = 1,
    UART_7BitData = 2,
    UART_8BitData = 3

}UART_DataLengthType;

typedef enum
{
    UART_ONEStopBit =0,
    UART_TWOStopBit =1
}UART_StopBitLengthType;

typedef enum
{
    UART_ParityBitDisabled=0,
    UART_ParityBitEnabled=1
}UART_ParityBitType;

typedef enum
{
    UART_EvenParity=1,
    UART_OddParity=0
}UART_ParityType;

typedef enum
{
    UART_FIFO_Enabled=1,
    UART_FIFO_Disabled=0
}UART_FIFO_StatusType;

typedef enum
{
    UART_2ByteTriggerLength = 0,

    UART_4ByteTriggerLength = 1,

    UART_8ByteTriggerLength = 2,

    UART_12ByteTriggerLength = 3,

    UART_14ByteTriggerLength = 4,

}UART_FIFO_TriggerLengthType;






typedef enum
{

    Requested=0,
    NotRequested

}RequestStatusType;

typedef enum
{
    IDLE_State,
    BUSY_State,
    SUSPENDED_State

}UART_ChannelStatus;
typedef enum
{
    INT_ENABLED=1,
    INT_DISABLED=0
}UART_INTStatusType;

typedef enum
{
    DOUBLE_SPEED
}SpeedModeType;



typedef struct
{
    UART_FIFO_TriggerLengthType TX_FIFO_TriggerLength;
    UART_ChannelStatus TX_Status;
    UART_INTStatusType TX_INT_Status;
    void (*TxHandlerPtr)(void) ;
}TxType;

typedef struct
{
    UART_FIFO_TriggerLengthType RX_FIFO_TriggerLength;
    UART_ChannelStatus RX_Status;
    UART_INTStatusType RX_INT_Status;
    void (*RxHandlerPtr)(void) ;

}RxType;


typedef struct
{
    u8 UARTNum;
    u32 BaudRate ;
    UART_DataLengthType DataLength;
    UART_StopBitLengthType StopLength ;
    UART_FIFO_StatusType FIFO_Status;
    UART_ParityBitType ParityBit ;
    UART_ParityType Parity_Type ;
    TxType TransmitterFifo_Config;
    RxType RecieverFifo_Config;
    u8 Speed_Mode;
}UART_module;


void UART_init(void);

UART_enumCheckType UART_enumRequestToSend (u8 copy_u8UARTID, u16 copy_DataLength , u8 * PtrBuffer);

UART_enumCheckType UART_enumRequestToRecieve (u8 copy_u8UARTID, u16 copy_DataLength , u8 * PtrBuffer);







#endif /* UART_INT_H_ */
