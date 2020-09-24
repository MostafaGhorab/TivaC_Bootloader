/*
 * GPIO_Utils.h
 *
 *  Created on: Oct 6, 2019
 *      Author: AhmedShawky
 */

#ifndef DIO_UTILS_H_
#define DIO_UTILS_H_
#include "DIO_types.h"
#include "DIO_MemMap.h"

#define GPIO_WRITE_DATA(PORT_NUM,MASK,DATA)    *((volatile u32*)(GPIODATA(PORT_NUM)+((MASK)<<2)))=DATA
#define GPIO_READ_DATA(PORT_NUM,MASK)          *((volatile u32*)(GPIODATA(PORT_NUM)+((MASK)<<2)))


#endif /* DIO_UTILS_H_ */
