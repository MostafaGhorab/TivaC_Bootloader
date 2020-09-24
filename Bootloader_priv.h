/*
 * Bootloader_priv.h
 *
 *  Created on: 20 May 2020
 *      Author: Ghorab
 */

#ifndef BOOTLOADER_PRIV_H_
#define BOOTLOADER_PRIV_H_


/*Boot config Register macros*/
#define CMT 3
#define KEY_value 0xA442
#define KEY_shift 16



/*General used macros*/
#define WELCOME_MESSAGE_SIZE 49
#define ERROR_MESSAGE_SIZE 13

/*Get version command macros*/
#define BL_GET_VER 'a'
#define BL_VERSION 0x00

/*flash macros*/
#define BL_GET_FPL 'b'
#define BL_FLASH_ERASE 'c'
#define BL_FLASH_WRITE 'd'
#define BL_FLASH_READ  'e'


/*Jump to certain adress macros*/
#define BL_JUMP_TO_ADDS 'f'




/* Private functions prototypes */
static void UART_privSend (u8 * Array , u32 BytesNo);
static void UART_privRecieve (u8 * Array , u16 BytesNo);
static void UART_priv_NewLine (void);
static void UnsignedIntToHexStringConverter(u32 n, u32 base, u8 sign, u8 *outbuf,u32 outbuf_len);
static  u32 get_crc(u8 *buff, u32 len) ;
static void BL_GetVersionHandler (void);
static void BL_GetFlashProLevelHandler (void);
static void BL_JumpToAddsHandler (void);
static void BL_FlashEraseHandler (void);
static void BL_FlashWriteHandler (void);








#endif /* BOOTLOADER_PRIV_H_ */
