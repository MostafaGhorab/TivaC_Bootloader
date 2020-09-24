/*
 * Bootloader_config.h
 *
 *  Created on: 18 May 2020
 *      Author: Ghorab
 */

#ifndef BOOTLOADER_CONFIG_H_
#define BOOTLOADER_CONFIG_H_


#define USER_VECTOR_OFFSET  0x00020000 /*location of start of user's Vector Table*/

#define MAX_CODE_LENGTH 255  //in bytes not words /* Thats used as a buffer for user to store the command and code, always add extra 5 bytes to max code length  */


#define CODE_LEN_APPROXIMATE 5 /*code len in kilobytes -approximated to upper kilo, ex if code len =3.5k put 4 here */


#endif /* BOOTLOADER_CONFIG_H_ */
