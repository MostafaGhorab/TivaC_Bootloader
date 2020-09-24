/*
 * FLASH_int.h
 *
 *  Created on: 21 May 2020
 *      Author: GHORAB
 */

#ifndef FLASH_INT_H_
#define FLASH_INT_H_

#include "std_types.h"
#include "BOOT_Mem_map.h"
#include "GPIO_Utils.h"
#include "Port.h"
#include "DIO.h"



typedef enum
{
    Flash_OK,
    Flash_NOK

}enum_FlashReturn;




enum_FlashReturn Flash_Erase(u32  FlashBaseAddress,u32 blockCount);
//enum_FlashReturn Flash_Write(const void* data, int wordCount);
enum_FlashReturn Flash_Write(u32  FlashBaseAddress ,  u32* data, u32 wordCount);
enum_FlashReturn Flash_Write_Byte(u32  FlashBaseAddress ,  u8* data, u32 wordCount);
void Flash_Read(u32  FlashBaseAddress , u32 * data, u32 wordCount);
//void Flash_Read(void* data, int wordCount);




#endif /* FLASH_INT_H_ */
