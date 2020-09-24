/*
 * Priv.c
 *
 *  Created on: Nov 24, 2019
 *      Author: AhmedShawky
 */

/*===============================================GetPortNum function================================================================================*/
#include "std_types.h"
#include "Priv.h"

extern const u8 PinsPerPort[PORTS_NUMBER];
void GPIO_enumGetPortNum(u8 PinId,u8 *PortNum)
{
	u8 i;
	u8 total=PinsPerPort[0]-1;

	if(PinId<=MaxPinNum)
	{
		for(i=0;i<PORTS_NUMBER;i++)
		{
			if(PinId<=total)
			{
				*(PortNum)=i;
				break;
			}
			total=total+PinsPerPort[i+1];
		}
	}
}
/*=================================================GetPinNum function===============================================================================*/

void GPIO_enumGetPinNum(u8 PinId,u8 *PinNum)
{
	u8 i;
	u8 remainder;
	u8 total=PinsPerPort[0];          /*just an initializing value so to hold the total number of pins when we subtract it from the pinID*/
	if(PinId<PinsPerPort[0])     /*then it must be the exact pinnum and needs no subtracion from the other ports' pin count */
	{
		*(PinNum)=PinId;
	}
	else                          /*then it is a value that is bigger than the first port's pin count and it needs to be subtracted from the other ports' pin count*/
	{
		for(i=0;i<PORTS_NUMBER;i++)
		{
			remainder = PinId-total;
			if(remainder<PinsPerPort[i+1])
			{
				*(PinNum)=remainder;
				break;
			}
			total=total+PinsPerPort[i+1];
		}
	}

}
/*===============================================utility function to get the max number of pins per port whatever the uC is=======================================*/
u8 GetMaxPortPinNum(u8 * PinPerPortArr)
{
	u8 i;
	u8 max;
	max=PinPerPortArr[0];
	for(i=1;i<PORTS_NUMBER;i++)
	{
		if(PinPerPortArr[i]>max)
		{
			max=PinPerPortArr[i];
		}
	}
	return max;
}



