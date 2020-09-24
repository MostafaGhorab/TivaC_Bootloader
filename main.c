/*
 * main.c
 *
 *  Created on: 1 May 2020
 *      Author: GHORAB
 */
#include "std_types.h"
#include "BOOT_Mem_map.h"
#include "UART_MemMap.h"
#include "GPIO_Utils.h"
#include "Port.h"
#include "DIO.h"
#include "UART_int.h"
#include "UART_priv.h"
#include "Bootloader_int.h"
#include "FLASH_int.h"

void progBootCfg_reg(void);
 const long int NOROM  ;
const u32 FFLASH = 0xDEADBEEF;


int ccc (void)
{
    const u32 where =10;
    u32 y = where;
    y++;
    y = FFLASH;
    y = NOROM;
    return where;


}








//PF4 switch ta7t 3l shemal
Dio_LevelType sw;
void main (void)
{


  int z =  ccc();

    Port_Init();
    UART_init () ;
    SET_BIT(UARTCTL(UART0),8);
    SET_BIT(UARTCTL(UART0),9);


    Port_SetPinMode(PORTA_PIN0,0x01);
    Port_SetPinMode(1,0x01);
    Port_SetPinMode (PORTF_PIN3,0x00);
    Port_SetPinMode (PORTF_PIN4,0x00);
    Dio_ReadChannel(PORTF_PIN4, &sw);
    //u8 dat[6] = {0x5,0xFF,0x11,0x22,0xAA,0xBB};
//    Flash_Write(0x00030000, dat, 2);
   //  Flash_Write_Byte(0x00030000,dat,6);

    // Flash_Erase(0x00030000, 2);
    //u32 t[2] ={0};
//    Flash_Read(0x00030000, t, 2);
    if (sw == 0) //pressed
    {


               void_JumpToUserCode ();

    }
    else
    {

      // Dio_WriteChannel(PORTF_PIN3,1); //go to bootloader


                     void_JumpToBootloader();

    }








    while(1)
    {




    }

}







/*
This function progBootCfg_reg is omnly called once to overwrite the flash register bootcgf
in order to access the in rom bootloader flashed by TIVAC vendor
                            DATA SHEET IMPORTANT NOTES
For example, if the BOOTCFG register is written and committed with the value of 0x00003C12,
then PB7 is examined at reset to determine if the ROM Boot Loader should be executed. If PB7 is
Low, the core unconditionally begins executing the ROM boot loader. If PB7 is High, then the
application in Flash memory is executed if the reset vector at location 0x0000.0004 is not
0xFFFF.FFFF. Otherwise, the ROM boot loader is executed.

U0Tx is not driven by the ROM boot loader until the auto-bauding process has completed. If U0Tx
is floating during this time, the receiver it is connected to may see transitions on the signal, which
could be interpreted by its UART as valid characters. To handle this situation, put a pull-up or
pull-down on U0Tx, providing a defined state for the signal until the ROM boot loader begins driving
U0Tx. A pull-up is preferred as it indicates that the UART is idle, rather than a pull-down, which
indicates a break condition.

write data to FMD
based on above value 3c02 FMC/FMC2 write key 0x71D5

 */
void progBootCfg_reg(void)
{



    // Write the desired boot configuration to the FMD register
    FMD =0x00003C12 ;  // configure the GPIO port and pin and polarity of pinb to check after booting to execute the bootloader if polarity is true

    // Write the address of the register which we wish to commit from table page 533 in data sheet
    FMA =  0x75100000;;

    // Write to non-vol 0x75100000;atile register (KEY + COMT bit)

    FMC  |=   ( (KEY_value <<KEY_shift) | (1<<CMT) ) ;


    //Poll COMT bit in the FMC register until the commit operation is complete it returns zero by hardware when last commit is done
    while( (GET_BIT(FMC,0)==1) && ( GET_BIT(FMC,3)==1 ) );

}




