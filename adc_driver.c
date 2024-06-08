/*adc_driver.c*/
/* LPC2129 inbuilt function */
#include "header.h"

#define DONE ((ADDR>>31)&1)

void adc_init(void)
{
	PINSEL1=0x15400000;		// PINSEL setting // P0.29 ->Ain2
	ADCR=0x00200400;		/*ADC setting using ADCR*/
}

u16 adc_read(u8 ch_num)
{
	u32 result=0;	 
	ADCR|=(1<<ch_num);		/*channel selection*/
	ADCR|=(1<<24);			/*start ADC*/
	while(DONE==0);			/*Monitor DONE flag*/
	ADCR^=(1<<24);			/*stop ADC*/
	ADCR^=(1<<ch_num);		/*Unselect ch_num*/
	result=(ADDR>>6)&0x3FF;	/*extract result*/
	return result;		
}
