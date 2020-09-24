
 /*
 *
 *  Created on: Nov 24, 2019
 *      Author: AhmedShawky
 */

#ifndef DIO_MEMMAP_H_
#define DIO_MEMMAP_H_


#define DIO_GEN_REG(PORT_NUM,OFFSET)                    PORTS_BASES[PORT_NUM]+OFFSET


#define GPIO_PORTA_BASE                        0x40004000
#define GPIO_PORTB_BASE                        0x40005000
#define GPIO_PORTC_BASE                        0x40006000
#define GPIO_PORTD_BASE                        0x40007000
#define GPIO_PORTE_BASE                        0x40024000
#define GPIO_PORTF_BASE                        0x40025000
#define GPIODATA_OFFSET                        0x000
#define GPIODATA(PORT_ID)                      DIO_GEN_REG(PORT_ID,GPIODATA_OFFSET)



#endif /* DIO_MEMMAP_H_ */
