/*
 * Port.c
 *
 *  Created on: Nov 23, 2019
 *      Author: AhmedShawky
 */

/*================================================== Set Pin Direction Function ================================================================*/
#include "GPIO_MemMap.h"
#include "Priv.h"
#include "Port.h"
#include "Port_Config.h"
#include "Port_Priv.h"
#include "utils.h"
#define GPIO_UNLOCK_VAL                                   0x4C4F434B
#define VECTKEY                                           0x05FA
#define SHIFT_BITS                                        4
const u32 PORTS_BASES[PORTS_NUMBER]={GPIO_PORTA_BASE,GPIO_PORTB_BASE,GPIO_PORTC_BASE,GPIO_PORTD_BASE,GPIO_PORTE_BASE,GPIO_PORTF_BASE};
const u8 PortIntNum[PORTS_NUMBER]={0,1,2,3,4,30};
extern const u8 PinsPerPort[PORTS_NUMBER];
extern const Port_ConfigType GroupsArr[NUM_OF_GROUPS];
/*============================================= Port initialization function ==================================================*/

void Port_Init(void)
{
	u8 LoopIndex;
	for(LoopIndex=0;LoopIndex<NUM_OF_GROUPS;LoopIndex++)
	{
		SET_BIT(RCGCGPIO,GroupsArr[LoopIndex].GroupId); /*ENABLING THE CLOCK*/
        GPIOLOCK(GroupsArr[LoopIndex].GroupId) = GPIO_UNLOCK_VAL;
        GPIOCR(GroupsArr[LoopIndex].GroupId) |= 0xff;   /*as we want all the values to reach PUR/PDR/DEN/and AFSEL*/
		if( (GroupsArr[LoopIndex].AlternateFunctionStatus)==AltFunc_EN)
		{
			GPIOAFSEL(GroupsArr[LoopIndex].GroupId) |= (GroupsArr[LoopIndex].AlternateFuncPinsMask);
		}
		GPIODIR(GroupsArr[LoopIndex].GroupId) |= (GroupsArr[LoopIndex].PinsDirection);
		GPIODEN(GroupsArr[LoopIndex].GroupId) |= (GroupsArr[LoopIndex].PinType);
		GPIOAMSEL(GroupsArr[LoopIndex].GroupId) |=~ (GroupsArr[LoopIndex].PinType);
		GPIODR2R(GroupsArr[LoopIndex].GroupId) |= (GroupsArr[LoopIndex].GPIODR2R);
		GPIODR4R(GroupsArr[LoopIndex].GroupId) |= (GroupsArr[LoopIndex].GPIODR4R);
		GPIODR8R(GroupsArr[LoopIndex].GroupId) |= (GroupsArr[LoopIndex].GPIODR8R);
		GPIOODR(GroupsArr[LoopIndex].GroupId) |= (GroupsArr[LoopIndex].GPIOODR);
		GPIOPDR(GroupsArr[LoopIndex].GroupId) |= (GroupsArr[LoopIndex].GPIOPDR);
		GPIOPUR(GroupsArr[LoopIndex].GroupId) |= (GroupsArr[LoopIndex].GPIOPUR);
	}
}

/*=========================================================== Set pin direction function ===============================================================*/

Port_enumerr Port_SetPinDirection( u8 Pin, Port_PinDirectionType Direction )
{
	u8 Loc_PinNumber;
	u8 Loc_PortNumber;
	if(Pin<=MaxPinNum)
	{
		GPIO_enumGetPinNum(Pin,&Loc_PinNumber);
		GPIO_enumGetPortNum(Pin,&Loc_PortNumber);
		GPIODIR(Loc_PortNumber)|=(1<<Loc_PinNumber);
		return OK;
	}
	else
	{
		return NOK;
	}

}

/*=========================================================== Set alternate function ========================================================*/
Port_enumerr Port_SetPinMode( u8 Pin, u8 Mode )
{
	u8 Loc_PinNumber;
	u8 Loc_PortNumber;
	if(Pin<=MaxPinNum)
	{
		GPIO_enumGetPinNum(Pin,&Loc_PinNumber);
		GPIO_enumGetPortNum(Pin,&Loc_PortNumber);
		GPIOPCTL(Loc_PortNumber)|=(Mode<<(Loc_PinNumber*SHIFT_BITS));
		return OK;
	}
	else
	{
		return NOK;
	}
}





