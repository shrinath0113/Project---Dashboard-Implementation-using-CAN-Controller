#include"header.h"

CAN2 v;
u8 HEAD,RIGHT,LEFT;

int main()

{
	s32 r,l;
	r=l=1;

	adc_init();
	can2_init();
	en_EINT_interrupts();
	config_vic();
	C2TFI1=4<<16;
	while(1)
	{

		

		if(HEAD)
		{
		C2TID1=0x101;
		C2TDA1=adc_read(1);
		C2CMR=0x21;

		delay_ms(100);	
			
		C2TID1=0x100;
		C2TDA1=adc_read(2);	
		C2CMR=0x21;
		delay_ms(100);
		}
		
		if(HEAD==0)
		{
		 C2TID1=0x50;
		 C2TDA1=0x20;
		 C2CMR=0x21;
		}

		if(RIGHT)
		{
			RIGHT=0;
	   		C2TID1=0x201;
	   		if(r)
			{
				C2TDA1=0x50;
				r=0;
				l=1;		
			}
			else
			{
				C2TDA1=0x60;
				r=1;		
			}	
			C2CMR=0x21;
		}

	   if(LEFT)
		{
	   		LEFT=0;
	   		C2TID1=0x202;
	   		if(l)
			{
				C2TDA1=0x30;
				l=0;
				r=1;		
			}
			else
			{
				C2TDA1=0x40;
				l=1;		
			}	
			C2CMR=0x21;
		}
	}

}
