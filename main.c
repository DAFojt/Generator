#include "iodefine.h"
#include "lcd.h"
#include "inline.h"
#define klawiatura_Obszar 0x20000
#define klawiatura_bufor (*(volatile unsigned char *)(klawiatura_Obszar+1))

//Zmienne globalne:
short odczyt;
short kl_odczyt = 20;

short Fzadane = 20;         //Startowa wartość częstotliwości przebiegu
short wypelnienie = 5;      //Startowa wartość wypełnienia przebiegu

char Xstop[] = "STOP  ";    //Napis wyświetlany na ekranie gdy PWM jest wyłączony
char Xstart[] = "START  ";  //Gdy włączony
char d_s[] = "D= ";         //Napis dla D(wypełnienia)
char f_s[] = "F= 0,10Hz";   //Dla F(częstotliwości)
short min, max;             //Wartości graniczne dla wypełnienia

short odczyt_procentowy;    //Wypełnienie przedstawione w sposób procentowy 1-100

char stan_pracy = 0;        //Określenie stanu pracy PWM - 0 OFF, 1 - ON

unsigned short count;       //Zliczanie
short counter = 0;
short gra = 0;


//------------ Program główny ----------------------
int main (void)
{
	IniLCD();							            //Restart wyswietlacza
	EkranStartowy();
	ClrScr();
	init_ITU0();								     //Inicjalizacja ITU0
	init_ITU2();								     //Inicjalizacja ITU2

	init_AC();										 //Inicjalizacja przetwornika AC
	stopPWM();

	while(1)							       //Glowna petla programu
	{
		if(ITU0.TSR.BIT.IMFA == 1)
		{
			ITU0.TSR.BIT.IMFA = 0;
			counter ++;
		}
		if(counter/100 == 1) 			//Realizacja programu raz na 100 cykli petli
		{
			counter = 0;					      //Reset zmiennej licznika
			PA.DR.BYTE^=0x01;
			EkranStartowy();				//Wyswietlenie ekranu startowego
			odczytaj_klawiature();		          //Odczyt klawiszy oraz ich obsluga
			klawisze_funkcje();		      //Wyswietlenie stanu pracy PWM na ekranie
			odczyt_AC();
			GotoXY(2,4);
//Skok kursora sluzacy do wyswietlenia tekstu w wybranej czesci ekranu glownego
			bin_bcd(czestotliwosc_kl(kl_odczyt), 1);
//Wyswietlanie czestotliwosci zadanej na ekranie glownym
			GotoXY(1,12);
			bin_bcd(odczyt_procentowy, 0);
//Wyswietlanie wypelnienia w formie procentowej na ekranie glownym
			obslugaProcentow(odczyt_procentowy);
		}
	}
}

//------------ Procedury ----------------------
void odczytaj_klawiature()  //Procedura nadzorujaca wcisniecie klawiszy 1 - 4
{
	unsigned char KL;
	KL = klawiatura_bufor&0x7f;

	if((KL == 0x7b)&&(stan_pracy == 0))
//Nadzorowanie klawisza odpowiedzialnego za uruchomienie PWM
	{
	stan_pracy = 1;
	startPWM(odczyt, wypelnienie);
	}
	if((KL == 0x77)&&(stan_pracy == 1))
//Nadzorowanie klawisza odpowiedzialnego za wylaczenie PWM
	{
	stan_pracy = 0;
	stopPWM();
	}
	if(KL == 0x7e)
//Klawisz dekrementujacy czestotliwosc
	{
		if(kl_odczyt > 20)
		kl_odczyt -= 1;

		Fzadane = kl_odczyt;
	}
	if(KL == 0x7d)
//Klawisz inkrementujacy czestotliwosc
	{
		if(kl_odczyt < 200)
		kl_odczyt += 1;
		Fzadane = kl_odczyt;
	}
}


short czestotliwosc(short a)     //Funkcja przeliczajaca czestotliwosc
{
	long b = (((long)a * 989)/1023 + 10);
	return b;
}

short czestotliwosc_kl(short a)
//Funkcja częstotliwości int na long
{
	long b = ((long)kl_odczyt);
	return b;
}

void klawisze_funkcje()
//Procedura wyswietlajaca na ekranie stan pracy PWM
{
	if(stan_pracy == 0)
		puts(Xstop, 1, 1);
	if(stan_pracy == 1)
		puts(Xstart, 1, 1);
}

//PWM
void startPWM(short f, short d)
//Start PWM
{
	init_ITU3();
}

void stopPWM(void)
//Stop PWM
{
	ITU.TSTR.BIT.STR3=0;
	ITU3.GRB = ITU3.GRA/2;
	ITU3.TIER.BYTE = 0xF8;
	ITU.TSTR.BIT.STR3=1;
}

void init_ITU3(void)
//Generacja PWM na ITU3
{
	ITU.TSTR.BIT.STR3=0; //stop licznika
	ITU3.TCNT = 0;
	ITU3.TCR.BYTE = 0xA3;
	ITU3.GRA = (short)((2000000L/10000));
	ITU3.GRB = (short)(((long)ITU3.GRA * wypelnienie)/100);
	ITU.TMDR.BIT.PWM3=1;
	ITU3.TIER.BYTE = 0xF9;
	ITU.TSTR.BIT.STR3=1;
	//start licznika
}

void init_ITU2(void)
//Kontrola czestotliwosci sygnalu PWM3
{
	ITU.TSTR.BIT.STR2=0; 							 //stop licznika
	ITU2.TCNT = 0;
	ITU2.TCR.BYTE = 0xA3;
	ITU2.GRA = (short)((100000L/Fzadane));
	ITU2.TIER.BYTE = 0xF9;
	ITU.TSTR.BIT.STR2=1; 							 //start licznika
}
//Koniec PWM

int puts(char* tabl, short  x, short y)
//Funkcja wstawiania pojedynczego znaku na ekran
{
	short i;
	GotoXY(x,y);
	for(i=0; i<16; i++)
	{
		if(tabl[i]==0)
		break;
		putchar(tabl[i]);
	}
	return i;
}

void init_AC(void) 							//Inicjalizacja przetwornika AC
{
	AD.ADCSR.BYTE = 0x3A;
}

void odczyt_AC(void)
//Procedura odczytu wartosci z przetwornika AC oraz zamiana pelnego zakresu odczytu z przetwornika na wartosc procentowa 0-100%
{
	 unsigned short odczyt_surowy;
	 odczyt_surowy = (unsigned short)AD.ADDRC;
	 odczyt_surowy >>=6;
	 odczyt = odczyt_surowy;
	 odczyt_procentowy = (short)odczyt*0.1;
	 if(odczyt_procentowy > 100) odczyt_procentowy = 100;

	 min = 50-(odczyt_procentowy/2);
	 max = 50+(odczyt_procentowy/2);
}







void init_ITU0(void) 							 	 //Inicjalizacja ITU0
{
	ITU.TSTR.BIT.STR0 = 0;
	ITU0.TCR.BYTE = 0xA1;
	ITU0.TIER.BYTE = 0x88;
	ITU0.TIER.BYTE = 0xF8;
	ITU.TSTR.BIT.STR0 = 1;
	ITU0.GRA = 7999;
}
													 //Ekran startowy wyswietlajacy sie po uruchomieniu programu
void EkranStartowy()
{
	puts(Xstart, 1, 1);
	short d = 5;
	short f = 10;
	puts(d_s, 1 ,10);
	puts(f_s, 2, 1);
}
													 //Procedura wyswietlajaca potrzebne informacje na ekranie LCD
void obslugaProcentow(short liczba)
{
	char tab[3];
	if(liczba<100)
	tab[0] = ' ';
	if(liczba<10)
	tab[1] = ' ';
	if(liczba==100)
	{
		GotoXY(2,12);
		putchar('M');
		putchar('A');
		putchar('X');
	}
	else
	{
		GotoXY(2,12);
		putchar(' ');
		putchar(' ');
		putchar(' ');
	}
	if(liczba==0)
	{
		GotoXY(2,12);
		putchar('M');
		putchar('I');
		putchar('N');
	}
	GotoXY(1,15);
	putchar('%');
}
void bin_bcd(short liczba, short dok)
//Procedura wyswietlajaca liczbe na ekran z zadana dokladnoscia 0-3
{
	char tab[4];
	short tysiace = liczba/ 1000;
//Przeliczanie konkretnych cyfr liczby
	short setki = liczba/100;
	short dziesiatki = (liczba - (setki * 100))/10;
	tab[0] = setki + 0x30;								 	//Przypisanie poszczegolnych cyfr do konkretnych komorek tablicy
	tab[1] = dziesiatki + 0x30;									tab[2] = liczba - setki * 100 - dziesiatki * 10 + 0x30;

	if(dok==0)
	{
		putchar(tab[0]);
		putchar(tab[1]);
		putchar(tab[2]);
	}
	else
	{
		if(dok == 3)
		{
			putchar(',');
			putchar(tab[0]);
			putchar(tab[1]);
			putchar(tab[2]);
		}
		if(dok == 2)
		{
			putchar(tab[0]);
			putchar(',');
			putchar(tab[1]);
			putchar(tab[2]);
		}
		if(dok == 1)
		{
			putchar(tab[0]);
			putchar(tab[1]);
			putchar(',');
			putchar(tab[2]);
		}
	}
}
