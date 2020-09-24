

/**
 * main.c
 */
#include "std_types.h"
#include "UART_int.h"
#include "UART_priv.h"
#include "UART_Config.h"
#include "UART_MemMap.h"
#include "utils.h"
extern void GPS_ReceptionDone(void);
void (*UART0_RX)(void)  = NULL;
void (*UART1_RX)(void)  = NULL;
void (*UART2_RX)(void)  = NULL;
void (*UART3_RX)(void)  = NULL;
void (*UART4_RX)(void)  = NULL;
void (*UART5_RX)(void)  = NULL;
void (*UART6_RX)(void)  = NULL;
void (*UART7_RX)(void)  = NULL;
void RX_UART0(void);
void RX_UART0(void)
{
//    UART0_RX();
}
void RX_UART1(void)
{
    UART1_RX();
}
void RX_UART2(void)
{
    UART2_RX();
}
void RX_UART3(void)
{
    UART3_RX();
}
void RX_UART4(void)
{
    UART4_RX();
}
void RX_UART5(void)
{
    UART5_RX();
}
void RX_UART6(void)
{
    UART6_RX();
}
void RX_UART7(void)
{
    UART7_RX();
}
u16 RecieveDataLength [NUMBER_OF_MODULES] = {0} ;

extern UART_module UART_ConfigArray [NUMBER_OF_MODULES];
BufferInfo TxBufferInfoArray [NUMBER_OF_MODULES]; /*intialize it*/
BufferInfo RxBufferInfoArray [NUMBER_OF_MODULES]; /*intialize it*/

u8 SendRequestFlag [NUMBER_OF_MODULES] = {0} ;
u8 RecieveRequestFlag [NUMBER_OF_MODULES] = {0} ;
u8 LookUpArray [NUMBER_OF_MODULES] ={0};
void(*(TX_Ptrtofuncarr[MaxNumOFmodules]))(void)={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

void(*(RX_Ptrtofuncarr[MaxNumOFmodules]))(void)={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

void(*RX_funcarr[MaxNumOFmodules])(void)={RX_UART0,RX_UART1,RX_UART2,RX_UART3,RX_UART4,RX_UART5,RX_UART6,RX_UART7};

#define RxFIFOTriggerLenShift 3

void  UART_init(void)
{


    u8 i=0;
    u8 UART_Num;
    for (i=0; i<NUMBER_OF_MODULES; i++)
    {
        UART_Num=UART_ConfigArray[i].UARTNum;
        TxBufferInfoArray [i].UART_NUM = UART_Num ;
        RxBufferInfoArray [i].UART_NUM = UART_Num ;
        RCGCUART |= (1<<UART_Num); //enable UART peripheral clock register
        CLR_BIT(UARTCTL(UART_Num),0); //disable UARTn
        UART_vidBaudRateCalc(i);  /*i is the index of the config array*/
        UARTLCRH(UART_Num)|=(UART_ConfigArray[i].ParityBit)<<PEN;  /*either Enabeled or diasabled parity*/
        UARTLCRH(UART_Num)|=(UART_ConfigArray[i].Parity_Type)<<EPS; /*0 for odd parity and one for even parity*/
        UARTLCRH(UART_Num)|=(UART_ConfigArray[i].StopLength)<<STP2; /*0 for one stop bit and one for two stop bits */
        UARTLCRH(UART_Num)|=(UART_ConfigArray[i].FIFO_Status)<<FEN;
        UARTLCRH(UART_Num)|=(UART_ConfigArray[i].DataLength)<<WLEN;
        UARTCC(UART_Num)|=CLOCK_SOURCE;    /* Either PIOSC (16 Mhz) or system clock */
        UARTCTL(UART_Num)|= UART_ConfigArray[i].Speed_Mode;
        if((UART_ConfigArray[i].TransmitterFifo_Config.TX_INT_Status)==INT_ENABLED)
        {
            UARTIM(UART_Num)|=(INT_ENABLED<<TXIM);
            UARTIFLS(UART_Num)|=(UART_ConfigArray[i].TransmitterFifo_Config.TX_FIFO_TriggerLength);  /*selecting the fifo length*/
            TX_Ptrtofuncarr[UART_Num] = UART_ConfigArray[i].TransmitterFifo_Config.TxHandlerPtr ;

        }
        if((UART_ConfigArray[i].RecieverFifo_Config.RX_INT_Status)==INT_ENABLED)
        {
            UARTIM(UART_Num)|=(INT_ENABLED<<RXIM);
            UARTIFLS(UART_Num)|=((UART_ConfigArray[i].RecieverFifo_Config.RX_FIFO_TriggerLength)<<RxFIFOTriggerLenShift);
            RX_Ptrtofuncarr[UART_Num] = UART_ConfigArray[i].RecieverFifo_Config.RxHandlerPtr ;
        }

        SET_BIT(UARTCTL(UART_Num),0); //Enable UARTn



    }
}

/*======================================================Request To Send=============================================================*/

UART_enumCheckType UART_enumRequestToSend (u8 copy_u8UARTID, u16 copy_DataLength , u8 * PtrBuffer)
{
    UART_enumCheckType ErrorFunctionValidation = okay ;
    u8 LoopIndex ;
    if (0!=copy_DataLength)
    {


        for (LoopIndex =0; LoopIndex<NUMBER_OF_MODULES;LoopIndex++)
        {

            if ((copy_u8UARTID == TxBufferInfoArray[LoopIndex].UART_NUM) && (UART_ConfigArray[UART_privGetConfigIndix(copy_u8UARTID)].TransmitterFifo_Config.TX_Status ==IDLE_State))
            {
                TxBufferInfoArray[LoopIndex].BufferLength = copy_DataLength;
                TxBufferInfoArray[LoopIndex].ptrToBuffer = PtrBuffer;
                SendRequestFlag[LoopIndex] = 1;
                UART_ConfigArray[UART_privGetConfigIndix(copy_u8UARTID)].TransmitterFifo_Config.TX_Status =SUSPENDED_State ;
                break;
            }



        }

        if (LoopIndex ==NUMBER_OF_MODULES )    //no break operation happened
        {
            ErrorFunctionValidation = nokay ;
        }
    }
    else
    {
        ErrorFunctionValidation=nokay;
    }
    return ErrorFunctionValidation ;
}

/*======================================================Request To Receive =============================================================*/
UART_enumCheckType UART_enumRequestToRecieve (u8 copy_u8UARTID, u16 copy_DataLength , u8 * PtrBuffer)
{

    UART_enumCheckType ErrorFunctionValidation = okay ;
    u8 LoopIndex ;
    if (0!=copy_DataLength)
    {

        for (LoopIndex =0; LoopIndex<NUMBER_OF_MODULES;LoopIndex++)
        {

            if ((copy_u8UARTID == RxBufferInfoArray[LoopIndex].UART_NUM) && (UART_ConfigArray[UART_privGetConfigIndix(copy_u8UARTID)].RecieverFifo_Config.RX_Status ==IDLE_State))
            {
                RxBufferInfoArray[LoopIndex].BufferLength = copy_DataLength;
                RxBufferInfoArray[LoopIndex].ptrToBuffer = PtrBuffer;
                RecieveRequestFlag[LoopIndex] = 1;

                UART_ConfigArray[UART_privGetConfigIndix(copy_u8UARTID)].RecieverFifo_Config.RX_Status =SUSPENDED_State ;

                break;
            }



        }

        if (LoopIndex ==NUMBER_OF_MODULES )    //no break operation happened
        {
            ErrorFunctionValidation = nokay ;
        }
    }
    else
    {
        ErrorFunctionValidation = nokay ;
    }

    return ErrorFunctionValidation ;



}

/*======================================================Get FIFO Status func=============================================================*/

UART_enumCheckType UART_PrivGetFIFOStatus (u8 copy_u8UARTnum, FIFO_Type copy_FIFO_TypeTx_Rx,FIFO_StatusType * StatusGetter )
{
    UART_enumCheckType ErrorFuncValid = okay ;

    if (copy_u8UARTnum > NUMBER_OF_MODULES)
    {
        ErrorFuncValid = nokay;
    }
    * StatusGetter= Available ;

    if (copy_FIFO_TypeTx_Rx == TxFIFO )
    {
        if (GET_BIT(UARTFR(copy_u8UARTnum),5)!=0) //if the TxFIFO is  full
        {
            *StatusGetter = NotAvailable ;
        }
    }

    else if (copy_FIFO_TypeTx_Rx == RxFIFO )
    {
        if (GET_BIT(UARTFR(copy_u8UARTnum),4)!=0) //if the TxFIFO is  Empty
        {
            *StatusGetter = NotAvailable ;
        }
    }
    return ErrorFuncValid ;
}
/*====================================================== Priv Send Char =============================================================*/
void UART_privSendChar(u8 copy_u8UARTID ,u8 Data)
{
    UARTDR(copy_u8UARTID)=Data;
    while( GET_BIT( UARTFR( copy_u8UARTID ) , 3 ) == 1 ); /* waits until the transmition completes ( Added by AZ )*/
}
/*====================================================== Priv Receive Char =============================================================*/
u8 UART_privRecieveChar(u8 copy_u8UARTID)
{
    u8 x;
    x=UARTDR(copy_u8UARTID) ;
    return x;
}

/*======================================================  Main Function ================================================================*/
void UART_mainFunc (void)
{
    u8 LoopIndex;
    u8 UART_ID ;
    u16 counter=0;
    FIFO_StatusType TxStatusGetter ;
    FIFO_StatusType RxStatusGetter ;
    //u8 RecieveDataLength [NUMBER_OF_MODULES] = {0} ;
    static u16 SentDataLength [NUMBER_OF_MODULES] = {0} ;
    for (LoopIndex = 0 ; LoopIndex<NUMBER_OF_MODULES ; LoopIndex ++ )
    {
        if (SendRequestFlag [LoopIndex] == 1)
        {
            UART_ID =  TxBufferInfoArray[LoopIndex].UART_NUM ;

            UART_PrivGetFIFOStatus (UART_ID, TxFIFO, &TxStatusGetter );
            while ( ( TxStatusGetter == Available ) && ( (SentDataLength [LoopIndex] )  < (TxBufferInfoArray[LoopIndex].BufferLength ) ) )
            {
                UART_privSendChar(UART_ID , TxBufferInfoArray[LoopIndex].ptrToBuffer[SentDataLength [LoopIndex] ]  ) ;
                SentDataLength [LoopIndex]++ ;
                UART_ConfigArray[UART_privGetConfigIndix(UART_ID)].TransmitterFifo_Config.TX_Status =BUSY_State ;
                UART_PrivGetFIFOStatus (UART_ID, TxFIFO, &TxStatusGetter );
                counter++;
                if((counter > MAX_LENGTH)&&( (SentDataLength [LoopIndex] )  != (TxBufferInfoArray[LoopIndex].BufferLength ) ))
                {
                    UART_ConfigArray[UART_privGetConfigIndix(UART_ID)].TransmitterFifo_Config.TX_Status =SUSPENDED_State ;
                    break;
                }

            }
            if (TxStatusGetter == NotAvailable) /*IF FIFO IS NOT AVAILABLE DONT SEND */
            {
                UART_ConfigArray[UART_privGetConfigIndix(UART_ID)].TransmitterFifo_Config.TX_Status =SUSPENDED_State ;
            }
            else if (( (SentDataLength [LoopIndex] )  == (TxBufferInfoArray[LoopIndex].BufferLength ) ) )
            {

                SendRequestFlag [LoopIndex] = 0 ;
                SentDataLength [LoopIndex] = 0;
                UART_ConfigArray[UART_privGetConfigIndix(UART_ID)].TransmitterFifo_Config.TX_Status =IDLE_State ;
                TX_Ptrtofuncarr[UART_ID] () ;
            }
        }


        if (RecieveRequestFlag [LoopIndex] == 1)
        {
            UART_ID =  RxBufferInfoArray[LoopIndex].UART_NUM ;
            UART_PrivGetFIFOStatus (UART_ID, RxFIFO, &RxStatusGetter );
            while ( ( RxStatusGetter == Available ) && ( (RecieveDataLength[LoopIndex] )  < (RxBufferInfoArray[LoopIndex].BufferLength ) ) )
            {
                RxBufferInfoArray[LoopIndex].ptrToBuffer[ RecieveDataLength [LoopIndex]] = UART_privRecieveChar(UART_ID) ;

                RecieveDataLength [LoopIndex]++ ;
                UART_ConfigArray[UART_privGetConfigIndix(UART_ID)].RecieverFifo_Config.RX_Status=BUSY_State ;
                UART_PrivGetFIFOStatus (UART_ID, RxFIFO, &RxStatusGetter );

            }
            if (RxStatusGetter == NotAvailable) /*IF FIFO IS NOT AVAILABLE DONT SEND */
            {
                UART_ConfigArray[UART_privGetConfigIndix(UART_ID)].RecieverFifo_Config.RX_Status =SUSPENDED_State ;
            }

            else if ( (RecieveDataLength[LoopIndex] )  == (RxBufferInfoArray[LoopIndex].BufferLength ) )
            {
                RxBufferInfoArray[LoopIndex].ptrToBuffer[ RecieveDataLength [LoopIndex]] = UART_privRecieveChar(UART_ID);
                RecieveRequestFlag [LoopIndex] = 0 ;
                RecieveDataLength [LoopIndex] = 0;
                UART_ConfigArray[UART_privGetConfigIndix(UART_ID)].RecieverFifo_Config.RX_Status =IDLE_State ;
                RX_Ptrtofuncarr[UART_ID] () ;
                RX_funcarr[UART_ID]();

            }
        }


    }


}
/*======================================================Get The index of a UARTID in UARTConfigArr[]=============================================================*/

u8 UART_privGetConfigIndix(u8 copy_u8ID)  //reverse function of lookup table gets the index from the uart ID module
{
    u8 i;
    for (i=0;i<NUMBER_OF_MODULES;i++)
    {
        if (LookUpArray[i]==copy_u8ID)
        {
            return i;
        }
    }
}
/*============================================================= Baud Rate Calculation =============================================================*/
void UART_vidBaudRateCalc(u8 i)
{
    u32 baudrate=UART_ConfigArray[i].BaudRate;
    u8  speed_mode;
    if(UART_ConfigArray[i].Speed_Mode == NORMAL_SPEED_MODE )
    {
        speed_mode = 16;
    }
    else
    {
        speed_mode = 8;
    }
    f32 calc=0;
    u16 FractionPart ;


    calc=CRYSTAL_FREQ/(baudrate*speed_mode*1.0);
    u16 integerPart= (u16)calc;
    calc=((calc-integerPart)*64)+0.5; //calculate the float part
    FractionPart = (u16) calc;
    UARTIBRD(UART_ConfigArray[i].UARTNum)=integerPart;
    UARTFBRD(UART_ConfigArray[i].UARTNum)=FractionPart;

}


void UART0_ISR (void)

{

    if (GET_BIT(UARTRIS(UART0),RXRIS))  /*The received FIFO level has passed through the condition defined in the UARTIFLS register */
    {
        RX_Ptrtofuncarr[UART0] () ;
        SET_BIT(UARTICR(UART0), 4);

    }
    else if (GET_BIT(UARTRIS(UART0),TXRIS)) /*The Transimmited FIFO level has passed through the condition defined in the UARTIFLS register */
    {
        TX_Ptrtofuncarr[UART0] () ;
        SET_BIT(UARTICR(UART0), 5);
    }


}
