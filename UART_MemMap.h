/*
 * UART_MemMap.h
 *
 *  Created on: 3 Dec 2019
 *      Author: WEST
 */

#ifndef UART_MEMMAP_H_
#define UART_MEMMAP_H_
#include "std_types.h"

#define UART_BASE (u32)0x4000C000

#define UARTn_BASE(UARTNUM)                  (u32)((UARTNUM<<(u16)12)+UART_BASE)

#define GPT_GEN_REG(UARTNUM,OFFSET)          (u32)(UARTn_BASE(UARTNUM) +OFFSET )

#define UARTDR_OFFSET   0x000

#define UARTRSR_OFFSET  0x004

#define UARTFR_OFFSET   0x018

#define UARTLCRH_OFFSET 0x02C
#define UARTCC_OFFSET   0xFC8
#define UARTFR_OFFSET   0x018
#define UARTIFLS_OFFSET 0x034
#define UARTIM_OFFSET   0x038
#define UARTICR_OFFSET  0x044
#define UARTRIS_OFFSET  0x03C
#define RCGCUART_OFFSET 0x618
#define UARTIBRD_OFFSET 0x024
#define UARTFBRD_OFFSET 0x028
#define UARTCTL_OFFSET  0x030
#define RCGCUART_BASE 0x400FE000


#define UARTLCRH(UARTNUM)      *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTLCRH_OFFSET) )
#define UARTDR(UARTNUM)        *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTDR_OFFSET) )
#define UARTRSR(UARTNUM)       *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTRSR_OFFSET) )
#define UARTFR(UARTNUM)        *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTFR_OFFSET) )
#define UARTIFLS(UARTNUM)      *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTIFLS_OFFSET) )
#define UARTIM(UARTNUM)        *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTIM_OFFSET) )
#define UARTICR(UARTNUM)       *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTICR_OFFSET) )
#define UARTRIS(UARTNUM)       *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTRIS_OFFSET) )
#define UARTCC(UARTNUM)        *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTCC_OFFSET) )
#define UARTIBRD(UARTNUM)      *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTIBRD_OFFSET) )
#define UARTFBRD(UARTNUM)      *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTFBRD_OFFSET) )
#define UARTCTL(UARTNUM)      *((volatile u32*) GPT_GEN_REG(UARTNUM,UARTCTL_OFFSET) )
#define RCGCUART               *((volatile u32*) (RCGCUART_BASE+RCGCUART_OFFSET))















#endif /* UART_MEMMAP_H_ */
