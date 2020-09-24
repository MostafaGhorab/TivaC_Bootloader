/*
 * GPIO_Int.H
 *
 *  Created on: Oct 6, 2019
 *      Author: AhmedShawky
 */

#ifndef DIO_H_
#define DIO_H_

#include "DIO_types.h"

typedef enum{
	OKAY,
	NOKAY
}DIO_enumerr;

DIO_enumerr Dio_ReadChannel( Dio_ChannelType ChannelId,Dio_LevelType*PtrToVal );
DIO_enumerr Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level );
DIO_enumerr Dio_ReadPort( Dio_PortType PortId ,Dio_PortLevelType*PtrToVal);
DIO_enumerr Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level );
DIO_enumerr Dio_ReadChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType*PtrToVal );
DIO_enumerr Dio_WriteChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level );

#endif /* DIO_H_ */
