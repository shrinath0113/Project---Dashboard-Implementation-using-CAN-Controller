#include"header.h"

void delay_sec(u32 sec)
{
	s32 a[]={15,60,30,15,15};
	u32 pclk;
	pclk=a[VPBDIV]*1000000-1;
	T0PC=0;
	T0PR=pclk; 					// delay for 1 sec
	T0TC=0;
	T0TCR=1;
	while(T0TC<sec);
	T0TCR=0;
}

void delay_ms(u32 ms)
{
	s32 a[]={15,60,30,15,15};
	u32 pclk;
	pclk=a[VPBDIV]*1000-1;
	T0PC=0;
	T0PR=pclk;  				// delay for 1 ms
	T0TC=0;
	T0TCR=1;
	while(T0TC<ms);
	T0TCR=0;
}

