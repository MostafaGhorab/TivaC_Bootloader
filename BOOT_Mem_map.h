/*
 * Mem_mao.h
 *
 *  Created on: 1 May 2020
 *      Author: Ghroab
 */
#include "std_types.h"
#ifndef BOOT_MEM_MAP_H_
#define BOOT_MEM_MAP_H_


#define FMC_BASE 0x400FD000
#define FMD_BASE 0x400FD000
#define FMA_BASE 0x400FD000
#define BCFG_BASE 0x400FE000
#define VTABLE_BASE 0xE000E000
#define FLASH_MEM_PROT_BASE 0x400FE000 //flash mem protecion








#define FMC_OFFSET 0x008
#define FMD_OFFSET 0x004
#define FMA_OFFSET 0x000
#define BCFG_OFFSET 0x1D0
#define VTABLE_OFFSET 0xD08

#define FMPRE0_OFFSET 0x130
#define FMPRE1_OFFSET 0x204
#define FMPRE2_OFFSET 0x208
#define FMPRE3_OFFSET 0x20C

#define FMPPE0_OFFSET 0x400
#define FMPPE1_OFFSET 0x404
#define FMPPE2_OFFSET 0x408
#define FMPPE3_OFFSET 0x40C




#define FMD               *( (volatile u32 *)(FMD_BASE + FMD_OFFSET ) )
#define FMC               *( (volatile u32 *)(FMC_BASE + FMC_OFFSET ) )
#define FMA               *( (volatile u32 *)(FMA_BASE + FMA_OFFSET ) )

#define BT_CFG            *( (volatile u32 *) (BCFG_BASE + BCFG_OFFSET ) )

#define VTABLE            * ((volatile u32 *)(VTABLE_OFFSET + VTABLE_BASE))


#define FMPRE0        * ((volatile u32 *)(FLASH_MEM_PROT_BASE + FMPRE0_OFFSET)) //first 64k bytes pRead
#define FMPRE1        * ((volatile u32 *)(FLASH_MEM_PROT_BASE + FMPRE1_OFFSET))
#define FMPRE2        * ((volatile u32 *)(FLASH_MEM_PROT_BASE + FMPRE2_OFFSET))
#define FMPRE3        * ((volatile u32 *)(FLASH_MEM_PROT_BASE + FMPRE3_OFFSET))

#define FMPPE0        * ((volatile u32 *)(FLASH_MEM_PROT_BASE + FMPPE0_OFFSET)) //Pprogram
#define FMPPE1        * ((volatile u32 *)(FLASH_MEM_PROT_BASE + FMPPE1_OFFSET))
#define FMPPE2        * ((volatile u32 *)(FLASH_MEM_PROT_BASE + FMPPE2_OFFSET))
#define FMPPE3        * ((volatile u32 *)(FLASH_MEM_PROT_BASE + FMPPE3_OFFSET))







#endif /* BOOT_MEM_MAP_H_ */
