/*
 * FLASH_prog.c
 *
 *  Created on: 21 May 2020
 *      Author: GHORAB
 */




#include "FLASH_int.h"


// The TM4C123gh6pm has 256 KiB of Flash memory located from addresses 0 to 0x0003FFFF
//  Make sure that the base address used here does not overlap with code and data!
//  Examine the linker's .map file to see where code/data is stored
//#define FLASH_BASE_ADDR         ((volatile u32*)0x00020000)

// This holds the key required for erase and write operations.  Set it during Enable()
static u16 flashKey = 0;
#define PAGE_SIZE 1024
#define ERASE_BIT 0x2
#define WRITE_BIT 0x1


enum_FlashReturn Flash_Erase(u32  FlashBaseAddress,u32 blockCount) /*block is 1k*/
{
    u32 i;

    if (BT_CFG & 0x10)
    {
        flashKey = 0xA442;
    }
    else
    {
        flashKey = 0x71D5;
    }



    for ( i = 0; i < blockCount; i++) {

        // Clear then set the OFFSET (17:0) with the write address
        FMA &= 0xFFFC0000; //clear from bit zero to 17

        // Blocks are erased on 1KiB boundaries, so multiply the index by 1024
        //  and add this to the base address
        FMA |= FlashBaseAddress + (i*PAGE_SIZE);

        // Set the ERASE command bit
        FMC = (flashKey << 16) | ERASE_BIT;

        // Poll the ERASE bit until it is cleared
        while (FMC & ERASE_BIT);

    }

    return Flash_OK;
}


enum_FlashReturn Flash_Write(u32  FlashBaseAddress ,  u32* data, u32 wordCount)
{

    u32 i;

    if (BT_CFG & 0x10)
    {
        flashKey = 0xA442;
    }
    else
    {
        flashKey = 0x71D5;
    }



    // Must erase the data first.  A write may only change a bit from 1 to 0, so if the
    //  bit is already zero, the write fails.  Erasing will set all bits to 1's.
    //  Calculate the number of 1KiB blocks that the data will span and erase that many.
    u32 blockCount = ((wordCount * sizeof(u32)) / 1024) + 1;
    Flash_Erase(FlashBaseAddress,blockCount );

    // Write one word at a time
    for ( i = 0; i < wordCount; i++) {

        // Set the data register.  This the word that will be written
        FMD = ((volatile u32*)data)[i];

        // Clear then set the OFFSET address field (17:0) with the write address
        FMA &= 0xFFFC0000;
        FMA |= FlashBaseAddress + (i * sizeof(u32));

        // Trigger a write operation
        FMC = (flashKey << 16) | WRITE_BIT;

        // Poll the WRITE bit until it is cleared.
        while (FMC & WRITE_BIT) ;

    }

    return Flash_OK;

}

enum_FlashReturn Flash_Write_Byte(u32  FlashBaseAddress ,  u8* data, u32 wordCount)
{



    u32 i;
    u8 j=0;
    u32 remaining_bytes=0;

    if (BT_CFG & 0x10)
    {
        flashKey = 0xA442;
    }
    else
    {
        flashKey = 0x71D5;
    }



    // Must erase the data first.  A write may only change a bit from 1 to 0, so if the
    //  bit is already zero, the write fails.  Erasing will set all bits to 1's.
    //  Calculate the number of 1KiB blocks that the data will span and erase that many.
   // u32 blockCount = ((wordCount * sizeof(u8)) / 1024) + 1;
    // Flash_Erase(FlashBaseAddress,blockCount );

    // Write one word at a time
    for ( i = 0; i < wordCount; i+=4) {

        FMD =0x0;

        // Set the data register.  This the word that will be written

        remaining_bytes = (wordCount - i) ;//get number of remaining bytes in data buffer

        if (remaining_bytes >= 4) //i will be refrencing index out of array range though
        {
            for(j=0;j<4;j++)
            {

                FMD |=   ( ((volatile u8*)data)[i+j] ) << (j*8) ;

            }

        }
        else
        {

            for(j=0;j<remaining_bytes;j++)
            {

                FMD |=   ( ((volatile u8*)data)[i+j] ) << (j*8) ;

            }



        }




        // Clear then set the OFFSET address field (17:0) with the write address
        FMA &= 0xFFFC0000;
        FMA |= FlashBaseAddress + i;

        // Trigger a write operation
        FMC = (flashKey << 16) | WRITE_BIT;

        // Poll the WRITE bit until it is cleared.
        while (FMC & WRITE_BIT) ;

    }

    return Flash_OK;

}



void Flash_Read(u32  FlashBaseAddress , u32 * data, u32 wordCount)
{
    u32 i;
    // Copy the count of bytes into the target data buffer
    for ( i = 0; i < wordCount; i++)
    {
        data[i] =  * ( (volatile u32*) (FlashBaseAddress+i*4) ) ;
    }

}
