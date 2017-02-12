/****************************************************************
KPIT Cummins Infosystems Ltd, Pune, India. - 05-Sept-2005.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*****************************************************************/

#include "inthandler.h"

extern void start (void);     /* Startup code (in start.s)  */
extern void stack (void);  /* stack from linker script   */

/**----------------------------------
**  Typedef for the function pointer
**-----------------------------------*/
#ifdef DEBUG
#define OFFSET 0x5A000000
#else
#define OFFSET 0
#endif

typedef void (*fp) (void);
#define VECT_SECT          __attribute__ ((section (".vects")))

const fp HardwareVectors[] VECT_SECT = {
  start,                    /* 0  Power-on reset, Program counter (PC) */  
(fp)0,			/*Reserved 1*/
(fp)0,			/*Reserved 2*/
(fp)0,			/*Reserved 3*/
(fp)0,			/*Reserved 4*/
(fp)0,			/*Reserved 5*/
(fp)0,			/*Reserved 6*/
OFFSET + INT_NMI,
OFFSET + INT_TRAP1,
OFFSET + INT_TRAP2,
OFFSET + INT_TRAP3,
OFFSET + INT_TRAP4,
OFFSET + INT_IRQ0,
OFFSET + INT_IRQ1,
OFFSET + INT_IRQ2,
OFFSET + INT_IRQ3,
OFFSET + INT_IRQ4,
OFFSET + INT_IRQ5,
(fp)0,			/*Reserved 18*/
(fp)0,			/*Reserved 19*/
OFFSET + INT_WOVI,
OFFSET + INT_CMI,
(fp)0,			/*Reserved 22*/
(fp)0,			/*Reserved 23*/
OFFSET + INT_IMIA0,
OFFSET + INT_IMIB0,
OFFSET + INT_OVI0,
(fp)0,			/*Reserved 27*/
OFFSET + INT_IMIA1,
OFFSET + INT_IMIB1,
OFFSET + INT_OVI1,
(fp)0,			/*Reserved 31*/
OFFSET + INT_IMIA2,
OFFSET + INT_IMIB2,
OFFSET + INT_OVI2,
(fp)0,			/*Reserved 35*/
OFFSET + INT_IMIA3,
OFFSET + INT_IMIB3,
OFFSET + INT_OVI3,
(fp)0,			/*Reserved 39*/
OFFSET + INT_IMIA4,
OFFSET + INT_IMIB4,
OFFSET + INT_OVI4,
(fp)0,			/*Reserved 43*/
OFFSET + INT_DEND0A,
OFFSET + INT_DEND0B,
OFFSET + INT_DEND1A,
OFFSET + INT_DEND1B,
(fp)0,			/*Reserved 48*/
(fp)0,			/*Reserved 49*/
(fp)0,			/*Reserved 50*/
(fp)0,			/*Reserved 51*/
OFFSET + INT_ERI0,
OFFSET + INT_RXI0,
OFFSET + INT_TXI0,
OFFSET + INT_TEI0,
OFFSET + INT_ERI1,
OFFSET + INT_RXI1,
OFFSET + INT_TXI1,
OFFSET + INT_TEI1,
OFFSET + INT_ADI,
};
