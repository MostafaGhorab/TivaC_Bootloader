/*
 * GPIO_INT.c
 *
 *  Created on: Dec 6, 2019
 *      Author: AhmedShawky
 */

#include"GPIO_INT.h"
#include"GPIO_MemMap.h"
#include"std_types.h"
#include "Port_Config.h"
#include"Port.h"
#include "Priv.h"
#include"utils.h"
extern const u8 PortIntNum[PORTS_NUMBER];
#define PIN0_INT_PIN                    1
#define PIN1_INT_PIN                    2
#define PIN2_INT_PIN                    4
#define PIN3_INT_PIN                    8
#define PIN4_INT_PIN                    16
#define PIN5_INT_PIN                    32
#define PIN6_INT_PIN                    64
#define PIN7_INT_PIN                    128
void func(void);   //just an empty initializing function to the array of pointer to functions
extern u8 PinsPerPort[PORTS_NUMBER];
extern const u32 PORTS_BASES[PORTS_NUMBER];
PtrtoFunc ISR_Ptr[8]={func,func,func,func,func,func,func,func};
const u8 PRIReg_BitShifts[PORTS_NUMBER]={5,13,21,29,5,21};
/*=================================================== Setting Interrupt event type to some pins selected by the mask ============================================*/
GPIOInt_enumerr GPIOInt_SetInterruptEvent(u8 PortId,u8 IntEvent,u8 IntMask)
{
	GPIOInt_enumerr ErrFuncValidation;
	if(PortId<PORTS_NUMBER)
	{
		switch(IntEvent)
		{
		case EVENT_FALL_EDGE :
			GPIOIS(PortId)&=(~(IntMask));  /*detection is configured to detect edges */
			GPIOIEV(PortId)&=(~(IntMask)); /*detection is configured to detect falling edges */
			break;
		case EVENT_RISE_EDGE :
			GPIOIS(PortId)&=(~(IntMask));
			GPIOIEV(PortId)|=(IntMask);  /*detection is configured to detect rising edges */
			break;
		case EVENT_BOTH_EDGE :
			GPIOIS(PortId)&=(~(IntMask));
			GPIOIBE(PortId)|=(IntMask);
			break;
		case EVENT_LOW_LEVEL :
			GPIOIS(PortId)|=(IntMask);     /*detection is configured to detect levels */
			GPIOIEV(PortId)&=(~(IntMask)); /*detection is configured to detect low levels */
			break;
		case EVENT_HIGH_LEVEL :
			GPIOIS(PortId)|=(IntMask);   /*detection is configured to detect levels */
			GPIOIEV(PortId)|=(IntMask);  /*detection is configured to detect high levels */
			break;
		}
		ErrFuncValidation = ok;
	}
	else
	{
		ErrFuncValidation = nok;
	}
	return ErrFuncValidation;
}
/*========================================================= Clear Interrupt Flag function for a specific pin ================================================================*/
GPIOInt_enumerr GPIOInt_ClrInterruptFlag(u8 PinId)
{
	u8 Loc_PinNumber;
	u8 Loc_PortNumber;
	GPIOInt_enumerr ErrFuncValidation;
	if(PinId<MaxPinNum)
	{
		GPIO_enumGetPinNum(PinId,&Loc_PinNumber);
		GPIO_enumGetPortNum(PinId,&Loc_PortNumber);
		GPIOICR(Loc_PortNumber)=1<<Loc_PinNumber;
		ErrFuncValidation = ok;
	}
	else
	{
		ErrFuncValidation = nok;
	}
	return ErrFuncValidation;
}
/*==================================================== get pin interrupt status ======================================================================*/
GPIOInt_enumerr GPIOInt_GetInterruptStatus(u8 PinId,Port_IntStatustype *IntStatusPtr)
{
	u8 Loc_PinNumber;
	u8 Loc_PortNumber;
	u8 retval;
	GPIOInt_enumerr ErrFuncValidation;
	if(PinId<MaxPinNum)
	{
		GPIO_enumGetPinNum(PinId,&Loc_PinNumber);
		GPIO_enumGetPortNum(PinId,&Loc_PortNumber);
		retval=((GPIORIS(Loc_PortNumber))&(1<<Loc_PinNumber))>>Loc_PinNumber;
		if(retval==1)
		{
			*(IntStatusPtr)=Pending;
		}
		else
		{
			*(IntStatusPtr)=Inactive;
		}
		ErrFuncValidation = ok;
	}
	else
	{
		ErrFuncValidation = nok;
	}
	return ErrFuncValidation;
}
/*==================================================== Interrupt initialization function for each pin =====================================================================*/
GPIOInt_enumerr GPIOInt_PinIntInit(u8 PinId,u8 IntEvent,u8 priority)
{
	u8 Loc_PinNumber;
	u8 Loc_PortNumber;
	GPIOInt_enumerr ErrFuncValidation;
	if(PinId<MaxPinNum)
	{
		GPIO_enumGetPinNum(PinId,&Loc_PinNumber);
		GPIO_enumGetPortNum(PinId,&Loc_PortNumber);
		/*to avoid false interrupt we follow the steps in the datasheet*/
		GPIOIM(Loc_PortNumber)=0x00;                                   /*first we disable the interrupt for the port*/
		GPIOInt_SetInterruptEvent(Loc_PortNumber,IntEvent,1<<Loc_PinNumber);      /*selecting the interrupt event,the mask here is 1<<(Pin I want to select)*/
		GPIOICR(Loc_PortNumber)=0xFF;                                  /*clearing GPIORIS by setting GPIOICR*/
		GPIOInt_SetIntPriority(Loc_PortNumber,priority);                  /*setting port priority*/
		//ENABELE PORT'S INTERRUPT
		SET_BIT(EN0,PortIntNum[Loc_PortNumber]);
		ErrFuncValidation=ok;
	}
	else
	{
		ErrFuncValidation=nok;
	}
	return ErrFuncValidation;
}

/*==================================================== Interrupt set priority function for each port ==============================================================*/
GPIOInt_enumerr GPIOInt_SetIntPriority(u8 PortId,u8 Priority)
{
	GPIOInt_enumerr ErrFuncValidation;
	if(PortId<PORTS_NUMBER)
	{
		if(PortId<=3)
		{
			PRI0=Priority<<PRIReg_BitShifts[PortId];
		}
		else if(PortId<=4)
		{
			PRI1=Priority<<PRIReg_BitShifts[PortId];
		}
		else
		{
			PRI7=Priority<<PRIReg_BitShifts[PortId];
		}
		ErrFuncValidation = ok;
	}
	else
	{
		ErrFuncValidation = nok;
	}
	return ErrFuncValidation;
}
/*=================================================Interrupt enable/Disable=========================================================================*/
GPIOInt_enumerr GPIOInt_IntEnable(u8 PinId)
{
	u8 Loc_PinNumber;
	u8 Loc_PortNumber;
	GPIOInt_enumerr ErrFuncValidation;
	if(PinId<MaxPinNum)
	{
		GPIO_enumGetPinNum(PinId,&Loc_PinNumber);
		GPIO_enumGetPortNum(PinId,&Loc_PortNumber);
		GPIOIM(Loc_PortNumber)|=1<<Loc_PinNumber;
		ErrFuncValidation = ok;
	}
	else
	{
		ErrFuncValidation = nok;
	}
	return ErrFuncValidation;
}

GPIOInt_enumerr GPIOInt_IntDisable(u8 PinId)
{
	u8 Loc_PinNumber;
	u8 Loc_PortNumber;
	GPIOInt_enumerr ErrFuncValidation;
	if(PinId<MaxPinNum)
	{
		GPIO_enumGetPinNum(PinId,&Loc_PinNumber);
		GPIO_enumGetPortNum(PinId,&Loc_PortNumber);
		GPIOIM(Loc_PortNumber)&=~(1<<Loc_PinNumber);
		ErrFuncValidation = ok;
	}
	else
	{
		ErrFuncValidation = nok;
	}
	return ErrFuncValidation;
}
/*================================================PORTA _ISR=================================================================================*/
void PORTA_ISR(void)
{
	u8 local_Int_Pin;
	u8 local_bit_num;
	for(local_bit_num=0;local_bit_num<PinsPerPort[PORTA];local_bit_num++)
	{
		local_Int_Pin=(GPIORIS(PORTA)&(1<<local_bit_num));                          /*This will allow me to know which pin has fired the interrupt*/
		if(local_Int_Pin==PIN0_INT_PIN)
		{

		    ISR_Ptr[PORTA_PIN0]();
			SET_BIT(GPIOICR(PORTA),local_bit_num);                                    // CLEARING THE GPIORIS AFTER EXECUTING THE
		}
		if(local_Int_Pin==PIN1_INT_PIN)
		{
		    ISR_Ptr[PORTA_PIN1]();
			SET_BIT(GPIOICR(PORTA),local_bit_num);                                   // CLEARING THE GPIORIS AFTER EXECUTING THE INT
		}
		if(local_Int_Pin==PIN2_INT_PIN)
		{
		    ISR_Ptr[PORTA_PIN2]();
			SET_BIT(GPIOICR(PORTA),local_bit_num);                                  // CLEARING THE GPIORIS AFTER EXECUTING THE
		}
		if(local_Int_Pin==PIN3_INT_PIN)
		{
		    ISR_Ptr[PORTA_PIN3]();
			SET_BIT(GPIOICR(PORTA),local_bit_num);                                 // CLEARING THE GPIORIS AFTER EXECUTING THE
		}
		if(local_Int_Pin==PIN4_INT_PIN)
		{
		    ISR_Ptr[PORTA_PIN4]();
			SET_BIT(GPIOICR(PORTA),local_bit_num);                                // CLEARING THE GPIORIS AFTER EXECUTING THE
		}
		if(local_Int_Pin==PIN5_INT_PIN)
		{

		    ISR_Ptr[PORTA_PIN5]();
			SET_BIT(GPIOICR(PORTA),local_bit_num);                                // CLEARING THE GPIORIS AFTER EXECUTING THE

		}
		if(local_Int_Pin==PIN6_INT_PIN)
		{

		    ISR_Ptr[PORTA_PIN6]();
			SET_BIT(GPIOICR(PORTA),local_bit_num);                               // CLEARING THE GPIORIS AFTER EXECUTING THE

		}
		if(local_Int_Pin==PIN7_INT_PIN)
		{
		    ISR_Ptr[PORTA_PIN7]();
			SET_BIT(GPIOICR(PORTA),local_bit_num);                             // CLEARING THE GPIORIS AFTER EXECUTING THE

		}
	}
}



//===================================================ISR func for each pin====================================================================================

void PORTA_PIN0_ISR(void(*Local_PIN0_ISR1)(void))
{
    ISR_Ptr[PORTA_PIN0]=Local_PIN0_ISR1;
}



void PORTA_PIN1_ISR(void(*Local_PIN1_ISR1)(void))
{
    ISR_Ptr[PORTA_PIN1]=Local_PIN1_ISR1;
}



void PORTA_PIN2_ISR(void(*Local_PIN2_ISR1)(void))
{
    ISR_Ptr[PORTA_PIN2]=Local_PIN2_ISR1;
}



void PORTA_PIN3_ISR(void(*Local_PIN3_ISR1)(void))
{
    ISR_Ptr[PORTA_PIN3]=Local_PIN3_ISR1;
}



void PORTA_PIN4_ISR(void(*Local_PIN4_ISR1)(void))
{
    ISR_Ptr[PORTA_PIN4]=Local_PIN4_ISR1;
}



void PORTA_PIN5_ISR(void(*Local_PIN5_ISR1)(void))
{
    ISR_Ptr[PORTA_PIN5]=Local_PIN5_ISR1;
}



void PORTA_PIN6_ISR(void(*Local_PIN6_ISR1)(void))
{
    ISR_Ptr[PORTA_PIN6]=Local_PIN6_ISR1;
}



void PORTA_PIN7_ISR(void(*Local_PIN7_ISR1)(void))
{
    ISR_Ptr[PORTA_PIN7]=Local_PIN7_ISR1;
}

void func(void)
{
    /*Hello I am empty*/
}

