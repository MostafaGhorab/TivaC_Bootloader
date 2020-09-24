/*
 * Priv.h
 *
 *  Created on: Nov 24, 2019
 *      Author: AhmedShawky
 */

#ifndef PRIV_H_
#define PRIV_H_

/*this file is made to include the functions and the #defines that we use internally through the drivers in order to ease the work*/
#include "std_types.h"


#define MaxPinNum        42   //(The sum of (pins'numbers per port))-1....loc?
#define MinPinNum        0
#define PORTS_NUMBER     6
#define PORTA_PIN_NUM    8
#define PORTB_PIN_NUM    8
#define PORTC_PIN_NUM    8
#define PORTD_PIN_NUM    8
#define PORTE_PIN_NUM    6
#define PORTF_PIN_NUM    5
#define MaxPortMask           0xff
void GPIO_enumGetPortNum(u8 PinId,u8 *PortNum);
void GPIO_enumGetPinNum(u8 PinId,u8 *PinNum);
u8 GetMaxPortPinNum(u8 * PinPerPortArr);



#endif /* PRIV_H_ */
