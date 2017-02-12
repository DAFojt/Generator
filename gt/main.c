/****************************************************************
KPIT Cummins Infosystems Ltd, Pune, India. - 10-Mar-2003.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*****************************************************************/

/*****************************************************************
program testowy, zadawanie czestotliwosci z potencjometry 100Hz - 5kHz z dokladnoscia do 10 Hz
ustawianie wypelnienia 5-95 z klawiatury, podobnie z klawiatury start i stop ukladu

*****************************************************************/

#include "iodefine.h"
#include "lcd.h"
#include "inline.h"


//napisy
unsigned char napis_KENER[] = "KENER";


//deklaracje funkcji z main

void Ekran_startowy(void);

short count;


//------------ wlasciwy program -----------------------------------

int main (void)
{
	
	IniLCD();
	Ekran_startowy();



	while(1)						//petla glowna
	{
		count = 20000;
		while(count--);

		PB.DR.BYTE^=0x01;			//sygnalizacja na LED
	}
	

}



//------- ekran startowy po wlaczeniu ukladu

void Ekran_startowy(void)
{
short liczba=8;  	
	GotoXY(1,1);
	putchar('a');
	GotoXY(1,3);
	putchar('b');
	GotoXY(2,3);
	putchar('7');
	liczba = liczba + 0x30;
	putchar(liczba);	
}
