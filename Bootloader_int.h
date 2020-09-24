/*
 * Bootloader_int.h
 *
 *  Created on: 18 May 2020
 *      Author: Ghorab
 */

#ifndef BOOTLOADER_INT_H_
#define BOOTLOADER_INT_H_
#include "std_types.h"
#include "BOOT_Mem_map.h"
#include "UART_MemMap.h"
#include "GPIO_Utils.h"
#include "Port.h"
#include "DIO.h"
#include "UART_int.h"
#include "UART_priv.h"
#include "Bootloader_config.h"
#include "Bootloader_priv.h"
#include "FLASH_int.h"



                                /******************************* DESCRIPTION***********************************/

/*
 * Bootloader is implemented with UART0 peripheral with baud rate = 9600 (Note: for UART0 you dont have to use usb to ttl converter just connect the tiva normally)
 * The code starts with checking PF4 (The bottom left switch in tiva C) if pressed it enters to bootloader mode if not it jumps to user's code
 * which is already flashed in another sector rather than 0x0 and defined in config.h
 * FOR SIMPLICITY YOU MAY USE LM FLASH PROGRAMMER TO PROGRAM YOUR CODE TO THE OFFSET YOU DEFINED IN config.h file
 * YOU should also realocate the vector table to the same offset in your program before flashing it using LM program
 * Note : commands are in asci format ex character a(command 1) is 0x61 in hexadecimal
 *
 *
 *                                                      Available COMMANDS:
 *                                                      -------------------
 *
 *COMMAND 1 : a ----> BL_GET_VER : this command is used to get the version of the controller
 *
 *
 *
 *
 *
 *
 */


                                            /*  functions prototypes    */

/*
 * This function is used to jump to the user's code according to the location specified in config.h file
 * It write to the MSP with value inside USER_VECTOR_OFFSET(location zero + user's offset) then assign a pointer to function  with the value
 * located in USER_VECTOR_OFFSET + 4 (RESET HANDLER) which the is the reset handler of user's code then jumps to this location
 * the user's code should be already flashed into this location and vector table realocation should be done already in user's code
 */

void void_JumpToUserCode (void);

void void_JumpToBootloader(void);


#endif /* BOOTLOADER_INT_H_ */
