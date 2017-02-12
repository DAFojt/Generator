/****************************************************************
KPIT Cummins Infosystems Ltd, Pune, India. - 10-Mar-2003.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*****************************************************************/

/*************************************************************************
Hardware initialisation routine called by the startup code before the
sections are initialised.  Bus controller, and other essential hardware
setup code should be placed here.

***************************************************************************/

#include "iodefine.h"

void hw_initialise (void)
{
	// TODO: add hardware initialisation code here
	
	BSC.ABWCR.BYTE=0xFB;	//ustaw szerokosc szyny danych dla poszczegolnych obszarow
	BSC.ASTCR.BYTE=0x0F;	//ustaw 3 stanowy cykl na szynie, cs6-2stanowy
	BSC.WCR.BYTE=0xF3;		//ustaw 3 wait-y na sztywno
	BSC.WCER.BYTE=0x0F;		//odblokuj wait na EEPROM, cs3
	
	PA.DDR=0xFF;			//port A jako wyjscia
	PB.DDR=0xFF;			//port B jako wyjscia
	P8.DDR=0xFF;			//port 8 jako wyjscia
	
	PA.DR.BYTE=0xAA;		//wymus stany pocz¹tkowe na porcie A
	PB.DR.BYTE=0x55;		//wymus stany pocz¹tkowe na porcie B
	
} 
