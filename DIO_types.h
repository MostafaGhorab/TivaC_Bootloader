#ifndef DIO_STDTYPES_H_
#define DIO_STDTYPES_H_

#include "std_types.h"
typedef unsigned char Dio_ChannelType;    /*it is used when declaring a channel id*/
typedef unsigned char Dio_PortType;       /*it is used when declaring a port id*/
typedef unsigned char Dio_PortLevelType;  /*This type is for the ports' returns and it is the size of the largest port in the uC*/
typedef unsigned char Dio_LevelType;      /*either 0x00 or 0x01*/


typedef struct{
	u8 mask;
	u8 offset;
	Dio_PortType port;
}Dio_ChannelGroupType;

#endif
