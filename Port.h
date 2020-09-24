/*
 * Port.h
 *
 *  Created on: Nov 23, 2019
 *      Author: AhmedShawky
 */

#ifndef PORT_H_
#define PORT_H_
#include "std_types.h"
#define NULL ((void *)0)
typedef enum{
	AltFunc_EN=0xff,
	AltFunc_DIS=0x00
}AlternatefuncStatusType;


typedef enum{
	OK,
	NOK
}Port_enumerr;

typedef enum{
	PORT_PIN_IN,
	PORT_PIN_OUT
}Port_PinDirectionType;


typedef struct
{
	u8 GroupId;
	u8 AlternateFuncPinsMask; /*this field is used to select the pins selected to use their alternate function */
	u8 PinsDirection;
	u8 PinType;
    AlternatefuncStatusType AlternateFunctionStatus;
	u8 GPIODR2R;
	u8 GPIODR4R;
	u8 GPIODR8R;
	u8 GPIOODR;
	u8 GPIOPUR;
	u8 GPIOPDR;
	void(*ISR_PtrToFunc)(void);
}Port_ConfigType;

//===============================================PORTA PINS=================================================================================
#define PORTA_PIN0                0
#define PORTA_PIN1                1
#define PORTA_PIN2                2
#define PORTA_PIN3                3
#define PORTA_PIN4                4
#define PORTA_PIN5                5
#define PORTA_PIN6                6
#define PORTA_PIN7                7
//===============================================PORTB PINS=================================================================================
#define PORTB_PIN0                8
#define PORTB_PIN1                9
#define PORTB_PIN2                10
#define PORTB_PIN3                11
#define PORTB_PIN4                12
#define PORTB_PIN5                13
#define PORTB_PIN6                14
#define PORTB_PIN7                15
//===============================================PORTC PINS=================================================================================
#define PORTC_PIN0                16
#define PORTC_PIN1                17
#define PORTC_PIN2                18
#define PORTC_PIN3                19
#define PORTC_PIN4                20
#define PORTC_PIN5                21
#define PORTC_PIN6                22
#define PORTC_PIN7                23
//===============================================PORTD PINS=================================================================================
#define PORTD_PIN0                24
#define PORTD_PIN1                25
#define PORTD_PIN2                26
#define PORTD_PIN3                27
#define PORTD_PIN4                28
#define PORTD_PIN5                29
#define PORTD_PIN6                30
#define PORTD_PIN7                31
//===============================================PORTE PINS=================================================================================
#define PORTE_PIN0                32
#define PORTE_PIN1                33
#define PORTE_PIN2                34
#define PORTE_PIN3                35
#define PORTE_PIN4                36
#define PORTE_PIN5                37
//===============================================PORTF PINS=================================================================================
#define PORTF_PIN0                38
#define PORTF_PIN1                39
#define PORTF_PIN2                40
#define PORTF_PIN3                41
#define PORTF_PIN4                42
//=====================================================PORTS===================================================================================
#define PORTA   0
#define PORTB   1
#define PORTC   2
#define PORTD   3
#define PORTE   4
#define PORTF   5

/*--------------------------------------------------------------------
 *                          Special consideration pins                |
 * These pins are locked to these functions and needs to be unlocked  |
 * and reconfigured in case of alternate use                          |
 *                                                                    |
 *  PA[1:0]   -->   UART0                                             |
 *  PA[5:2]   -->   SSI0                                              |
 *  PB[3:2]   -->   I1C0                                              |
 *  PC[3:0]   -->   JTAG                                              |
 *  PD[7]     -->   GPIO                                              |
 *  PF[0]     -->   GPIO                                              |
 --------------------------------------------------------------------*/

void Port_Init(void);
Port_enumerr Port_SetPinDirection( u8 Pin, Port_PinDirectionType Direction );
Port_enumerr Port_SetPinMode( u8 Pin, u8 Mode );




#endif /* PORT_H_ */
