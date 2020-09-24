/*
 * Bootloader_prog.c
 *
 *  Created on: 18 May 2020
 *      Author: Ghorab
 */

#include "Bootloader_int.h"

#define HEX_BASE     16
#define ASCII_TO_HEX 55 /*This is just a direct mapping between ASCII and HEX decimal values as the user enters an
                         adress ex: 0xFFFFFFFF             */
#define FLASH_START 0x00000000
#define FLASH_END   0x0003FFFF
#define SRAM_START  0x20000000
#define SRAM_END    0x220FFFFF

/*UART CALL BACK variables*/
extern u8 G_UART_sendFinished ; /*call back function sets this flag  when UART finishes sending */
extern u8 G_UART_RecFinished ;

/*global variables*/
void ( * ptr_reset_handler) (void);





void void_JumpToUserCode (void)
{

    //   VTABLE= (USER_VECTOR_OFFSET << 9);
    // u32 a = __get_MSP();
    u32 MSP_value =        * ((volatile u32 * )  USER_VECTOR_OFFSET);
    __set_MSP(MSP_value);
    ptr_reset_handler =  (void ( *) () ) (* ((volatile u32 * ) ( USER_VECTOR_OFFSET+4) ));
    ptr_reset_handler (); //enter user's app code

}


void void_JumpToBootloader (void)
{
    u8 Buffer[1]; /*array is allocated for recieving command */
    u8 Error_arr[ERROR_MESSAGE_SIZE]="CRC ERROR!\r\n\n";
    u8 welcome_arr[WELCOME_MESSAGE_SIZE] = "Welcome to Bootloader,Please send your command:\r\n"  ;
    u8 u8_command;
    u8 u8_CRC_Check = 1;


   // UART_privSend (welcome_arr,WELCOME_MESSAGE_SIZE);

    while (1)
    {

        UART_privRecieve ( Buffer, 1); /*first byte will contain the command recieved */
        u8_command = Buffer [0] ;

        switch (u8_command)
        {

        case BL_GET_VER :   /*this command needs 4 following bytes COMMAND (1) + CRC (4) as specified in documentation file */

            // UART_privRecieve ( Buffer,4 ); //crc
            //  void_calculate_CRC (); //still not implemented
            if (u8_CRC_Check == 1)
            {
                BL_GetVersionHandler ();

            }
            else
            {
                UART_privSend(Error_arr, ERROR_MESSAGE_SIZE);
            }

            break  ;


        case BL_GET_FPL :

            BL_GetFlashProLevelHandler();

            break;

        case BL_FLASH_ERASE :

            BL_FlashEraseHandler();

            break;

        case BL_FLASH_WRITE :



            BL_FlashWriteHandler();

            break;

        case BL_FLASH_READ :

            break;

        case BL_JUMP_TO_ADDS :

            BL_JumpToAddsHandler ();

            break ;


























        }



    }






}



static void BL_GetVersionHandler (void)
{
    static u8 reply_message[24] = {"Bootloader version is: "};
    u8 version = BL_VERSION + '0' ;
    UART_privSend(reply_message ,23);
    UART_privSend(&version ,1);
    UART_priv_NewLine ();

}

static void  BL_GetFlashProLevelHandler(void)
{

    u32  local_protectionLevel [8] = {FMPRE0,FMPPE0,FMPRE1,FMPPE1,FMPRE2,FMPPE2,FMPRE3,FMPPE3};
    static u8 prot_level_reply[34] = {"Sectorx ReadProt   ProgEraseProt\n\r"};
    static u8 arr_sectors[4] [8] = {
                                    {"Sector0 "},
                                    {"Sector1 "},
                                    {"Sector2 "},
                                    {"Sector3 "},
    };
    static u8 space_char = ' ' ;
    static u8 hex_symbol [3] ="0x";
    static u8 EachSector [9][8] = {0};    /*Each sector is 64kb crossponding to one regitser
                              first 8+1 8 crossponds to number of registers +1 it needs extra space used by function so extra 8 bytes are used
                              other 8 is the output bytes of the register converted from u32 to its hex but as ascii char ;0xFFFF.FFFF is the the default value*/
    u8 Reg_loop_index =0 ;
    u8 j;


    UART_privSend ( prot_level_reply, 34 );
    UART_priv_NewLine ();


    for (j = 0 ;j <4 ; j++ )
    {
        /*printf("0x%c%C",u[0],u[1],2); input 255 -> 0xFE*/
        /*example to use n = 15 , base = 16 , sign = ' ' , pointer to buffer ->F */

        UART_privSend (  &(arr_sectors[j][0]), 8 );
        UnsignedIntToHexStringConverter ( local_protectionLevel [Reg_loop_index],HEX_BASE,' ',EachSector[Reg_loop_index] ,8);
        UART_privSend (  hex_symbol, 2 );
        UART_privSend (  EachSector[Reg_loop_index] , 8 );
        Reg_loop_index++;

        UART_privSend (  &space_char , 1 );

        UnsignedIntToHexStringConverter ( local_protectionLevel [Reg_loop_index],HEX_BASE,' ',EachSector[Reg_loop_index] ,8);
        UART_privSend (  hex_symbol, 2 );
        UART_privSend (  EachSector[Reg_loop_index] , 8 );
        Reg_loop_index++;
        UART_priv_NewLine ();
    }


}

static void  BL_FlashEraseHandler(void)
{

    static u8 erase_reply_message[] = {"Enter base address in hex format ex: 0x0000000F not 0xF: "};
    static u8 erase_reply2_message [] = {"Enter number of pages (1kB sections) to erase ex:-0x01->0xFF-: "};
    static u8 OutOfRangeMessage2[] = "This address is out of range!\r\n";

    u8 Address [10];
    u8 PagesNumber[4];
    static u32 EraseBaseAddress=0;
    static u8 PagesCount=0;

    u8 i;
    u8 j =0;
    u8 input_error =0;

    UART_privSend(erase_reply_message ,sizeof(erase_reply_message)-1);
    UART_privRecieve(Address, 10);

    UART_privSend(erase_reply2_message ,sizeof(erase_reply2_message)-1);
    UART_privRecieve(PagesNumber, 4);

    for (i=0;i<10;i++) /*convert from ex 'F' to F in hexa or 15 decimal this should be representing 4 bytes in u32 adress variable*/
    {
        if ( (Address[i] >= '0') && (Address[i] <= '9') )
        {
            Address[i] = Address[i] - '0' ;
        }
        else if ( (Address[i] >= 'A') && (Address[i] <= 'F') )
        {
            Address[i] = Address[i] - ASCII_TO_HEX ;
        }
        else if (Address[i] == 'x')
        {

        }
        else
        {
            input_error = 1;
        }
    }
    PagesCount =0;
    EraseBaseAddress=0;

    for (i=9;i>1;i--)
    {

        EraseBaseAddress |=  ( Address[i] << (j* 4) );
        j++;

    }

    j=0;

    for (i=0;i<4;i++) /*convert from ex 'F' to F in hexa or 15 decimal this should be representing 4 bytes in u32 adress variable*/
    {
        if (PagesNumber[i] >= '0' && PagesNumber[i] <= '9' )
        {
            PagesNumber[i] = PagesNumber[i] - '0' ;
        }
        else if ( (PagesNumber[i] >= 'A') && (PagesNumber[i] <= 'F') )
        {
            PagesNumber[i] = PagesNumber[i] - ASCII_TO_HEX ;
        }

        else if (PagesNumber[i] == 'x')
        {

        }
        else
        {
            input_error = 1;
        }
    }

    for (i=3;i>1;i--)
    {

        PagesCount |=  ( PagesNumber[i] << (j* 4) );
        j++;

    }



    if ( (EraseBaseAddress <= FLASH_END) && (PagesCount<= 0xFF) && (PagesCount > 0) && (input_error ==0))
    {
        Flash_Erase(EraseBaseAddress, PagesCount );
    }
    else
    {
        UART_privSend(OutOfRangeMessage2 ,sizeof(OutOfRangeMessage2)-1);
    }



}




static void BL_FlashWriteHandler (void)
{

    u8 buffer[200]={0}; //total size of pac
    u32 CRC_recieved=0;
    u32 CRC_Calculated =0;
    u32 memory_adress=0;
    u32 data_length;
    u32 base_adress=0;
    ptr_reset_handler =  (void ( *) () ) (* ((volatile u32 * ) ( USER_VECTOR_OFFSET+4) ));

    static u8 send = 'a'; //acknowledge for hand shaking
    UART_privSend(&send, 1);

    u8 erase_count =0;

    while (1)
    {

        UART_privRecieve (& (buffer[0] ), 1); //rec lenghth
        UART_privSend(&send, 1); //send ack


        if (buffer[0]!=0)
        {


            UART_privRecieve ( &(buffer[1]),buffer[0] -1);


            /* implement code handling here*/

            CRC_recieved = * ((u32 *) (buffer +buffer[0]+1-4 )) ; //extracting crc
            CRC_Calculated =  get_crc(buffer,buffer[0]-4+1 ); //calculate crc for my data
            memory_adress = * ((u32 *) (& (buffer[2]) )); //extracting mem adress
            data_length =  buffer[6];             //only one byte no need for type casting

            if (erase_count == 0)
            {
                erase_count ++;
                Flash_Erase(memory_adress,CODE_LEN_APPROXIMATE );
                ptr_reset_handler = (void ( *) () ) (* ((volatile u32 * ) ( & (buffer[11]) )));
            }


            if (CRC_recieved == CRC_Calculated )
            {
                if ( (memory_adress+buffer[0]) <= FLASH_END )  //adress boundary is within flash range
                {

                    Flash_Write_Byte(memory_adress,&(buffer[7]),data_length);


                }
                else  //error in adress(may be another LED ON to inidicate this error)
                {


                }



            }
            else //error in uploading firmware jump to certian piece of code to make user know(LED=ON) to reset and repeat process
            {


            }

            UART_privSend(&send, 1);

        } //sending is finished jump b2a

        else
        {

           ptr_reset_handler (); //enter user's app code

        }

    }



}

static  void BL_JumpToAddsHandler (void)
{
    static u8 jump_reply_message[] = {"Enter address in hex format ex: 0x0000000F not 0xF: "};
    static u8 OutOfRangeMessage[] = "This address is out of range!\r\n";
    void  (* JumpPointerFunc ) (void);


    u8 Address [10];
    u32 jump_address;
    u8 i;
    u8 j =0;

    UART_privSend(jump_reply_message ,sizeof(jump_reply_message)-1);
    UART_privRecieve(Address, 10);
    for (i=0;i<10;i++) /*convert from ex 'F' to F in hexa or 15 decimal this should be representing 4 bytes in u32 adress variable*/
    {
        if (Address[i] >= '0' && Address[i] <= '9' )
        {
            Address[i] = Address[i] - '0' ;
        }
        else
        {
            Address[i] = Address[i] - ASCII_TO_HEX ;
        }
    }

    for (i=9;i>1;i--)
    {

        jump_address |=  ( Address[i] << (j* 4) );
        j++;

    }

    /*    check whether this code could be jump to or not within SRAM range or FLASH range     */

    if ( ( jump_address <= FLASH_END ) || ( jump_address >= SRAM_START && jump_address <= SRAM_END ) )
    {
        // jump_address = * ((volatile u32 *)jump_address);
        // jump_address++ ; /*This to set the T bit to be in Thumb mode not Arm mode instruction set */
        JumpPointerFunc = (void ( *) (void) ) jump_address ;
        JumpPointerFunc ();
    }
    else
    {
        UART_privSend(OutOfRangeMessage ,sizeof(OutOfRangeMessage)-1);
    }

}



static void UART_privSend (u8 * Array , u32 BytesNo )
{

    UART_enumRequestToSend(UART0,BytesNo,Array);
    while (G_UART_sendFinished == 0)
    {
        UART_mainFunc();
    }
    G_UART_sendFinished = 0;

}

static void UART_privRecieve (u8 * Array , u16 BytesNo)
{

    UART_enumRequestToRecieve(UART0,BytesNo,Array);
    while (G_UART_RecFinished == 0)
    {
        UART_mainFunc();
    }
    G_UART_RecFinished = 0;

}

static void UART_priv_NewLine (void)
{
    static u8 new [2] = "\n\r";
    UART_privSend(new,2);
}




/*printf("0x%c%C",u[0],u[1]); input 255 -> 0xFE*/
/*example to use n = 15 , base = 16 , sign = ' ' , pointer to buffer ->F */
static void UnsignedIntToHexStringConverter(u32 n, u32 base, u8 sign, u8 *outbuf,u32 outbuf_len)
{

    u32 i = 12;
    u32 j = 0;
    u32 m ;

    for ( m=0 ; m<outbuf_len; m++)
    {
        outbuf[m]  = 0;
    }

    do{
        outbuf[i] = "0123456789ABCDEF"[n % base];
        i--;
        n = n/base;
    }while( n > 0);

    if(sign != ' '){   /* ' ' is no sign indecation */
        outbuf[0] = sign;
        ++j;
    }

    while( ++i < 13){
        outbuf[j++] = outbuf[i];
    }

    outbuf[j] = 0;

}

//This function computes the 4 byte CRC(CRC32) using polynomial method
//Please refer these links for more details
//https://community.st.com/thread/18626
//http://www.st.com/content/ccc/resource/technical/document/application_note/39/89/da/89/9e/d7/49/b1/DM00068118.pdf/files/DM00068118.pdf/jcr:content/translations/en.DM00068118.pdf
//http://www.hackersdelight.org/hdcodetxt/crc.c.txt
//http://www.zlib.net/crc_v3.txt

static u32 get_crc(u8 *buff, u32 len)
{
    u32 i;
    u32 n;
    u32 Crc = 0XFFFFFFFF;
    u32 data =0;

    for( n = 0 ; n < len ; n++ )
    {
         data = buff[n];
        Crc = Crc ^ data;
        for(i=0; i<32; i++)
        {

        if (Crc & 0x80000000)
            Crc = (Crc << 1) ^ 0x04C11DB7; // Polynomial used in STM32
        else
            Crc = (Crc << 1);
        }

    }

  return(Crc);
}







