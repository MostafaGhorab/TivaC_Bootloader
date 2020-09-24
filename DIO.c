/*
 * GPIO_Pogram.c
 *
 *  Created on: Oct 12, 2019
 *      Author: AhmedShawky
 */
#include "DIO.h"
#include "DIO_Config.h"
#include "DIO_MemMap.h"
#include "std_types.h"
#include "DIO_types.h"
#include "DIO_Utils.h"
#include "Priv.h"


u8 PinsPerPort[PORTS_NUMBER]={PORTA_PIN_NUM,PORTB_PIN_NUM,PORTC_PIN_NUM,PORTD_PIN_NUM,PORTE_PIN_NUM,PORTF_PIN_NUM}; //Array that holds the number of pins per port
extern u32 PORTS_BASES[PORTS_NUMBER];
/*====================================================Write Channel=================================================================================================*/

DIO_enumerr Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
	u8 Loc_PinNumber;
	u8 Loc_PortNumber;
	if(ChannelId<=MaxPinNum)
	{
		GPIO_enumGetPinNum(ChannelId,&Loc_PinNumber);
		GPIO_enumGetPortNum(ChannelId,&Loc_PortNumber);
		GPIO_WRITE_DATA(Loc_PortNumber,1<<Loc_PinNumber,Level<<Loc_PinNumber);
		return OKAY;
	}
	else
	{
		return NOKAY;
	}

}

/*==========================================================Write Port=======================================================================================*/

DIO_enumerr Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level )
{
	u8 mask;
	u8 MaxPinNumber;                /*holds the number of the highest number of pins per port in the uC*/
	if(PortId<=PORTS_NUMBER)
	{
		MaxPinNumber=GetMaxPortPinNum(PinsPerPort);
		mask=(MaxPortMask)&((MaxPortMask)>>(MaxPinNumber-PinsPerPort[PortId])); /*this line makes the port fully masked whatever is its number of pins EX:0xff for 8 pins and 0x3f for 6 pins*/
		GPIO_WRITE_DATA(PortId,mask,Level);
		return OKAY;
	}
	else
	{
		return NOKAY;
	}
}
/*================================================Read Channel Val==================================================================================*/

DIO_enumerr Dio_ReadChannel( Dio_ChannelType ChannelId,Dio_LevelType*PtrToVal )
{
	u8 Loc_PinNumber;
	u8 Loc_PortNumber;
	if(ChannelId<=MaxPinNum)
	{
		GPIO_enumGetPinNum(ChannelId,&Loc_PinNumber);
		GPIO_enumGetPortNum(ChannelId,&Loc_PortNumber);
		*(PtrToVal)=(GPIO_READ_DATA(Loc_PortNumber,1<<Loc_PinNumber))>>Loc_PinNumber;
		return OKAY;
	}
	else
	{
		return NOKAY;
	}
}

/*==============================================Read Port Val=========================================================================================*/

DIO_enumerr Dio_ReadPort( Dio_PortType PortId ,Dio_PortLevelType*PtrToVal)
{
	u8 mask;
	u8 MaxPinNumber;                /*holds the number of the highest number of pins per port in the uC*/
	if(PortId<=PORTS_NUMBER)
	{
		MaxPinNumber=GetMaxPortPinNum(PinsPerPort);
		mask=(MaxPortMask)&((MaxPortMask)>>(MaxPinNumber-PinsPerPort[PortId])); /*this line makes the port fully masked whatever is its number of pins EX:0xff for 8 pins and 0x3f for 6 pins*/
		*(PtrToVal)=GPIO_READ_DATA(PortId,mask);
		return OKAY;
	}
	else
	{
		return NOKAY;
	}
}

/*=================================================Write Group Val================================================================================*/
DIO_enumerr Dio_WriteChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level )
{
	u8 Loc_PortNumber;
	u8 Loc_mask;
	u8 Loc_Offset; /*it is the shift of the data from the LSB*/
	if((ChannelGroupIdPtr->port)<=PORTS_NUMBER)
	{
		Loc_PortNumber=ChannelGroupIdPtr->port;
		Loc_mask=ChannelGroupIdPtr->mask;
		Loc_Offset=ChannelGroupIdPtr->offset;
		GPIO_WRITE_DATA(Loc_PortNumber,Loc_mask,(Level<<Loc_Offset));
		return OKAY;
	}
	else
	{
		return NOKAY;
	}

}
/*=================================================Read Group Val================================================================================*/
DIO_enumerr Dio_ReadChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType*PtrToVal )
{
	u8 Loc_PortNumber;
	u8 Loc_mask;
	u8 Loc_Offset; /*it is the shift of the data from the LSB*/
	if((ChannelGroupIdPtr->port)<=PORTS_NUMBER)
	{
		Loc_PortNumber=ChannelGroupIdPtr->port;
		Loc_mask=ChannelGroupIdPtr->mask;
		Loc_Offset=ChannelGroupIdPtr->offset;
		*(PtrToVal)=((GPIO_READ_DATA(Loc_PortNumber,Loc_mask))>>Loc_Offset);
		return OKAY;
	}
	else
	{
		return NOKAY;
	}

}
