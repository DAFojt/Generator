;/****************************************************************
KPIT Cummins Infosystems Ltd, Pune, India. - 05-Sept-2005.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*****************************************************************/

/*Include file for 3048F CPU */
#include "inthandler.h"
#include "iodefine.h"
extern short Fzadane;
extern short wypelnienie;
extern short kl_odczyt;
extern short odczyt;
int ink_dek = 1;
short wypelnienie_robocze = 0;
extern short min, max, odczyt_procentowy;

void INT_NMI(void)
{
	/*add your code here*/
}
void INT_TRAP1(void)
{
	/*add your code here*/
}
void INT_TRAP2(void)
{
	/*add your code here*/
}
void INT_TRAP3(void)
{
	/*add your code here*/
}
void INT_TRAP4(void)
{
	/*add your code here*/
}
void INT_IRQ0(void)
{
	/*add your code here*/
}
void INT_IRQ1(void)
{
	/*add your code here*/
}
void INT_IRQ2(void)
{
	/*add your code here*/
}
void INT_IRQ3(void)
{
	/*add your code here*/
}
void INT_IRQ4(void)
{
	/*add your code here*/
}
void INT_IRQ5(void)
{
	/*add your code here*/
}
void INT_WOVI(void)
{
	/*add your code here*/
}
void INT_CMI(void)
{
	/*add your code here*/
}
void INT_IMIA0(void)
{
	/*add your code here*/
}
void INT_IMIB0(void)
{
	/*add your code here*/
}
void INT_OVI0(void)
{
	/*add your code here*/
}
void INT_IMIA1(void)
{
	/*add your code here*/
}
void INT_IMIB1(void)
{
	/*add your code here*/
}
void INT_OVI1(void)
{
	/*add your code here*/
}
int wypelnienie_robocze_przekane_z_IMIA3;
void INT_IMIA2(void)
{
	ITU2.TSR.BIT.IMFA = 0;
		ITU2.GRA = (short)((100000L/Fzadane));
			if(ink_dek == 1)
	{
		wypelnienie++;	
		
		if(wypelnienie >= 100)
			ink_dek = 0;
	}
	else if(ink_dek == 0)
	{
		wypelnienie--;	
		
		if(wypelnienie < 0)
			ink_dek = 1;
	}
	
	wypelnienie_robocze = wypelnienie;
	
	if(wypelnienie>max)
	{
	wypelnienie_robocze = max;
	}
	
	else if(wypelnienie<min)
	{
	wypelnienie_robocze = min;
	}
}
void INT_IMIB2(void)
{
	/*add your code here*/
}
void INT_OVI2(void)
{
	/*add your code here*/
}



void INT_IMIA3(void)  //Realizacja modyikacji sygnalu PWM w zaleznosci od ustawionego wypelnienia
{
	ITU3.TSR.BIT.IMFA = 0;


	
	ITU3.GRB = (short)(((long)ITU3.GRA * wypelnienie_robocze)/100);
}
void INT_IMIB3(void)
{
	/*add your code here*/
}
void INT_OVI3(void)
{
	/*add your code here*/
}
void INT_IMIA4(void)
{
	/*add your code here*/
}
void INT_IMIB4(void)
{
	/*add your code here*/
}
void INT_OVI4(void)
{
	/*add your code here*/
}
void INT_DEND0A(void)
{
	/*add your code here*/
}
void INT_DEND0B(void)
{
	/*add your code here*/
}
void INT_DEND1A(void)
{
	/*add your code here*/
}
void INT_DEND1B(void)
{
	/*add your code here*/
}
void INT_ERI0(void)
{
	/*add your code here*/
}
void INT_RXI0(void)
{
	/*add your code here*/
}
void INT_TXI0(void)
{
	/*add your code here*/
}
void INT_TEI0(void)
{
	/*add your code here*/
}
void INT_ERI1(void)
{
	/*add your code here*/
}
void INT_RXI1(void)
{
	/*add your code here*/
}
void INT_TXI1(void)
{
	/*add your code here*/
}
void INT_TEI1(void)
{
	/*add your code here*/
}
void INT_ADI(void)
{
	/*add your code here*/
}
