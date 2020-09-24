/*
 * MemMap.h
 *
 *  Created on: Oct 5, 2019
 *      Author: AhmedShawky
 */

#ifndef GPIO_MEM_MAP_H_
#define GPIO_MEM_MAP_H_
#include "DIO_types.h"


#define GPIO_GEN_REG(PORT_NUM,OFFSET)                    PORTS_BASES[PORT_NUM]+OFFSET
#define GPIO_PORTA_BASE                        0x40004000
#define GPIO_PORTB_BASE                        0x40005000
#define GPIO_PORTC_BASE                        0x40006000
#define GPIO_PORTD_BASE                        0x40007000
#define GPIO_PORTE_BASE                        0x40024000
#define GPIO_PORTF_BASE                        0x40025000
#define GPIODIR_OFFSET                         0x400
#define GPIOIS_OFFSET                          0x404
#define GPIOIBE_OFFSET                         0x408
#define GPIOIEV_OFFSET                         0x40C
#define GPIOIM_OFFSET                          0x410
#define GPIORIS_OFFSET                         0x414
#define GPIOMIS_OFFSET                         0x418
#define GPIOICR_OFFSET                         0x41C
#define GPIOAFSEL_OFFSET                       0x420
#define GPIODR2R_OFFSET                        0x500
#define GPIODR4R_OFFSET                        0x504
#define GPIODR8R_OFFSET                        0x508
#define GPIOODR_OFFSET                         0x50C
#define GPIOPUR_OFFSET                         0x510
#define GPIOPDR_OFFSET                         0x514
#define GPIOSLR_OFFSET                         0x518
#define GPIODEN_OFFSET                         0x51C
#define GPIOLOCK_OFFSET 					   0x520
#define GPIOCR_OFFSET                          0x524
#define GPIOAMSEL_OFFSET 					   0x528
#define GPIOPCTL_OFFSET 					   0x52C
#define GPIOADCCTL_OFFSET                      0x530
#define GPIODMACTL_OFFSET                      0x534
#define GPIOPeriphID4_OFFSET                   0xFD0
#define GPIOPeriphID5_OFFSET 				   0xFD4
#define GPIOPeriphID6_OFFSET                   0xFD8
#define GPIOPeriphID7_OFFSET                   0xFDC
#define GPIOPeriphID0_OFFSET                   0xFE0
#define GPIOPeriphID1_OFFSET                   0xFE4
#define GPIOPeriphID2_OFFSET                   0xFE8
#define GPIOPeriphID3_OFFSET                   0xFEC
#define GPIOPCellID0_OFFSET                    0xFF0
#define GPIOPCellID1_OFFSET                    0xFF4
#define GPIOPCellID2_OFFSET                    0xFF8
#define GPIOPCellID3_OFFSET                    0xFFC

//==================================================INTERRUPT REGISTERS ==========================================================
#define EN0_OFFSET                             0x100
#define EN1_OFFSET                             0x104
#define EN2_OFFSET                             0x108
#define EN3_OFFSET                             0x10C
#define EN4_OFFSET                             0x110
#define ENn_BASE                               0xE000E000

#define DIS0_OFFSET                            0x180
#define DIS0_BASE                              0xE000E000

#define PEND0_OFFSET                           0x200
#define PEND0_BASE							   0xE000E000

#define UNPEND0_OFFSET                         0x280
#define UNPEND0_BASE						   0xE000E000

#define ACTIVE0_OFFSET                         0x300
#define ACTIVE0_BASE						   0xE000E000

#define PRI0_OFFSET                            0x400
#define PRI0_BASE						       0xE000E000

#define SWTRIG_OFFSET                          0xF00
#define SWTRIG_BASE						       0xE000E000

#define APINT_OFFSET                           0xD0C
#define APINT_BASE						       0xE000E000

#define PRI1_OFFSET                            0x404
#define PRI1_BASE						       0xE000E000

#define PRI7_OFFSET                            0x41C
#define PRI7_BASE                              0xE000E000

//===========================================================REGISTERS============================================================



#define GPIODIR(PORT_ID)                 *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIODIR_OFFSET)))
#define GPIOIS(PORT_ID)                  *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOIS_OFFSET)))
#define GPIOIBE(PORT_ID)                 *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOIBE_OFFSET)))
#define GPIOIEV(PORT_ID)                 *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOIEV_OFFSET)))
#define GPIOIM(PORT_ID)                  *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOIM_OFFSET)))
#define GPIORIS(PORT_ID)                 *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIORIS_OFFSET)))
#define GPIOMIS(PORT_ID)                 *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOMIS_OFFSET)))
#define GPIOICR(PORT_ID)                 *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOICR_OFFSET)))
#define GPIOAFSEL(PORT_ID)               *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOAFSEL_OFFSET)))
#define GPIODR2R(PORT_ID)                *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIODR2R_OFFSET)))
#define GPIODR4R(PORT_ID)                *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIODR4R_OFFSET)))
#define GPIODR8R(PORT_ID)                *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIODR8R_OFFSET)))
#define GPIOODR(PORT_ID)                 *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOODR_OFFSET)))
#define GPIOPUR(PORT_ID)                 *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPUR_OFFSET)))
#define GPIOPDR(PORT_ID)                 *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPDR_OFFSET)))
#define GPIOSLR(PORT_ID)                 *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOSLR_OFFSET)))
#define GPIODEN(PORT_ID)                 *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIODEN_OFFSET)))
#define GPIOLOCK(PORT_ID)                *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOLOCK_OFFSET)))
#define GPIOCR(PORT_ID)                  *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOCR_OFFSET)))
#define GPIOAMSEL(PORT_ID)               *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOAMSEL_OFFSET)))
#define GPIOPCTL(PORT_ID)                *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPCTL_OFFSET)))
#define GPIOADCCTL(PORT_ID)              *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOADCCTL_OFFSET)))
#define GPIODMACTL(PORT_ID)              *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIODMACTL_OFFSET)))
#define GPIOPeriphID4(PORT_ID)           *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPeriphID4_OFFSET)))
#define GPIOPeriphID5(PORT_ID)           *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPeriphID5_OFFSET)))
#define GPIOPeriphID6(PORT_ID)           *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPeriphID6_OFFSET)))
#define GPIOPeriphID7(PORT_ID)           *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPeriphID7_OFFSET)))
#define GPIOPeriphID0(PORT_ID)           *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPeriphID0_OFFSET)))
#define GPIOPeriphID1(PORT_ID)           *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPeriphID1_OFFSET)))
#define GPIOPeriphID2(PORT_ID)           *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPeriphID2_OFFSET)))
#define GPIOPeriphID3(PORT_ID)           *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPeriphID3_OFFSET)))
#define GPIOPCellID0(PORT_ID)            *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPCellID0_OFFSET)))
#define GPIOPCellID1(PORT_ID)            *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPCellID1_OFFSET)))
#define GPIOPCellID2(PORT_ID)            *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPCellID2_OFFSET)))
#define GPIOPCellID3(PORT_ID)            *((volatile u32*)(GPIO_GEN_REG(PORT_ID,GPIOPCellID3_OFFSET)))




//===================================================CLOCK GATING CONTROL REGISTERS======================================================
#define RCGC_BASE                        0x400FE000
#define RCGC_GPIO_OFFSET                 0x608
#define RCGCGPIO                         *((volatile u32*)(RCGC_BASE+RCGC_GPIO_OFFSET))
//==================================================INTERRUPTS' REGISTERS================================================================
#define ENn_REG_SIZE                  32
#define EN0                          *((volatile u32*)(ENn_BASE+EN0_OFFSET))
#define EN1                          *((volatile u32*)(ENn_BASE+EN1_OFFSET))
#define EN2                          *((volatile u32*)(ENn_BASE+EN2_OFFSET))
#define EN3                          *((volatile u32*)(ENn_BASE+EN3_OFFSET))
#define EN4                          *((volatile u32*)(ENn_BASE+EN4_OFFSET))
#define DIS0                         *((volatile u32*)(DIS0_BASE+DIS0_OFFSET))
#define PEND0                        *((volatile u32*)(PEND0_BASE+PEND0_OFFSET))
#define UNPEND0                      *((volatile u32*)(UNPEND0_BASE+UNPEND0_OFFSET))
#define ACTIVE0                      *((volatile u32*)(ACTIVE0_BASE+ACTIVE0_OFFSET))
#define PRI0                         *((volatile u32*)(PRI0_BASE+PRI0_OFFSET))
#define SWTRIG                       *((volatile u32*)(SWTRIG_BASE+SWTRIG_OFFSET))
#define APINT                        *((volatile u32*)(APINT_BASE+APINT_OFFSET))
#define PRI1                         *((volatile u32*)(PRI1_BASE+PRI1_OFFSET))
#define PRI7                         *((volatile u32*)(PRI7_BASE+PRI7_OFFSET))

#endif /* GPIO_MEM_MAP_H_ */
