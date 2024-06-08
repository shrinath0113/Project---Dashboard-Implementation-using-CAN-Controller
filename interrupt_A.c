#include"header.h"

extern u8 HEAD,RIGHT,LEFT;

//u8 IGNI,LEFT,RIGHT;

void EINT0_Handler(void) __irq
{
//	IGNI=1;
	RIGHT=1;
	EXTINT|=0x1;			// clear EINT0 intrrupt flag
	VICVectAddr=0x0;		// to finish the isr
}

void EINT1_Handler(void) __irq
{
//	LEFT=1;
	LEFT=1;
	EXTINT|=0x2;			// clear EINT1 intrrupt flag
	VICVectAddr=0x0;		// to finish the isr
}

void EINT2_Handler(void) __irq
{
//	RIGHT=1;
	HEAD^=1;
	EXTINT|=0x4;			// clear EINT2 intrrupt flag
	VICVectAddr=0x0;		// to finish the isr
}

void en_EINT_interrupts(void)
{
	PINSEL0|=0xA0000000;		// P0.14 is EINT1 and P0.15 is EINT2
	PINSEL1|=0x1;		 		// P0.16 is EINT0
	EXTMODE=0x7;				// EINT0 | EINT1 | EINT2 is edge Triggered
	EXTPOLAR=0x0;				// EINT0 | EINT1 | EINT2 is active low 
								// EINT0 | EINT1 | EINT2 is falling edge sensitive
}

void config_vic(void)
{
	VICIntSelect=0;

	VICVectCntl1=14|(1<<5);
	VICVectAddr1=(u32)EINT0_Handler;

	VICVectCntl2=15|(1<<5);
	VICVectAddr2=(u32)EINT1_Handler;

	VICVectCntl3=16|(1<<5);
	VICVectAddr3=(u32)EINT2_Handler;

	VICIntEnable|=(1<<14)|(1<<15)|(1<<16);
}




