/*
 * Port_Config.c
 *
 *  Created on: Nov 23, 2019
 *      Author: AhmedShawky
 */

#include "std_types.h"
#include "Priv.h"
#include "Port.h"
#include "Port_Config.h"


const Port_ConfigType GroupsArr[NUM_OF_GROUPS]={
		{
				0x00,         /*GroupId*/
				0x3f,         /*Alternate func pins mask*/
				0xf2,         /* PinsDirectionField */
				0xff,	      /* PinType -> 1 for digital,0 for analog */
				AltFunc_EN,   /*Alternate function Enabled or disabled*/
				0xff,         /* 2mA configuration */
				0x00,         /* 4mA configuration */
				0x00,         /* 8mA configuration */
				0x00,         /* Open drain configuration */
				0x00,         /* Pull up configuration */
				0x00,         /* Pull down configuration */
				NULL             /*HandlerFunction*/
		},

		{
				0x01,  		  /*GroupId*/
				0x03,  		  /*Alternate func pins mask*/
				0x02,  		  /* PinsDirectionField */
				0x03,		  /* PinType -> 1 for digital,0 for analog */
				AltFunc_EN,   /*Alternate function Enabled or disabled*/
				0x00,         /* 2mA configuration */
				0x00,         /* 4mA configuration */
				0x00,         /* 8mA configuration */
				0x00,         /* Open drain configuration */
				0x00,         /* Pull up configuration */
				0x00,         /* Pull down configuration */
				0             /*HandlerFunction*/
		},

		{
				0x02,   	  /*GroupId*/
				0x00,   	  /*Alternate func pins mask*/
				0xff,   	  /* PinsDirectionField */
				0xff,		  /* PinType -> 1 for digital,0 for analog */
				AltFunc_EN,   /*Alternate function Enabled or disabled*/
				0x00,         /* 2mA configuration */
				0x00,         /* 4mA configuration */
				0x00,         /* 8mA configuration */
				0x00,         /* Open drain configuration */
				0x00,         /* Pull up configuration */
				0x00,         /* Pull down configuration */
				0             /*HandlerFunction*/
		},

		{
				0x03,   	  /*GroupId*/
				0x00,   	  /*Alternate func pins mask*/
				0xff,   	  /* PinsDirectionField */
				0xff,		  /* PinType -> 1 for digital,0 for analog */
				AltFunc_EN,   /*Alternate function Enabled or disabled*/
				0x00,   	  /* 2mA configuration */
				0x00,    	  /* 4mA configuration */
				0x00,    	  /* 8mA configuration */
				0x00,    	  /* Open drain configuration */
				0x00,   	  /* Pull up configuration */
				0x00,   	  /* Pull down configuration */
				0             /*HandlerFunction*/
		},

		{
				0x04,   	  /*GroupId*/
				0x03,    	  /*Alternate func pins mask*/
				0x32,    	  /* PinsDirectionField (THIS PORT IS 6 PINS) */
				0x3f,		  /* PinType -> 1 for digital,0 for analog (THIS PORT IS 6 PINS) */
				AltFunc_EN,   /*Alternate function Enabled or disabled*/
				0x00,   	  /* 2mA configuration */
				0x00,    	  /* 4mA configuration */
				0x00,   	  /* 8mA configuration */
				0x00,   	  /* Open drain configuration */
				0x00,   	  /* Pull up configuration */
				0x00,    	  /* Pull down configuration */
				0             /*HandlerFunction*/
		},

		{
				0x05,  		   /*GroupId*/
				0x00,   	   /*Alternate func pins mask*/
				0x08,   	   /* PinsDirectionField (THIS PORT IS 5 PINS) */
				0x1f,	       /*PinType -> 1 for digital,0 for analog (THIS PORT IS 5 PINS) */
				AltFunc_EN,    /*Alternate function Enabled or disabled*/
				0x1f,    	   /* 2mA configuration */
				0x00,    	   /* 4mA configuration */
				0x00,    	   /* 8mA configuration */
				0x00,   	   /* Open drain configuration */
				0x10,  		   /* Pull up configuration */
				0x00,  	       /* Pull down configuration */
				0              /*HandlerFunction*/
		}
};






