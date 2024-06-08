#include"header.h"

CAN2 v;
u8 HEAD,RIGHT,LEFT;

int main()

{
	s32 h,r,l;
	h=r=l=1;

	adc_init();
	can2_init();
	en_EINT_interrupts();
	config_vic();
	while(1)
	{
//		C2TID1=TEMPERATURE_ID;
		v.id=0x101;
//		C2TFI1=4<<16;
		v.dlc=0x4;
//		C2TDA1=adc_read(1);
		v.byteA=adc_read(1);
//		C2CMR=0x21;
		can2_tx(v);

		delay_ms(100);	
			
//		C2TID1=SPEED_ID;
		v.id=0x100;		
//		C2TFI1=4<<16;
		v.dlc=0x4;
//		C2TDA1=adc_read(2);	
		v.byteA=adc_read(1);
//		C2CMR=0x21;
		can2_tx(v);
		delay_ms(100);
		if(HEAD)
		{
		 	HEAD=0;
//			C2TID1=HEADLIGHT_ID;
//			C2TFI1=4<<16;
			v.id=0x50;
			v.dlc=0x4;
			if(h)
			{
//				C2TDA1=HEADLIGHT_ON;
				v.byteA=0x10;
				h=0;		
			}
			else
			{
//				C2TDA1=HEADLIGHT_OFF;
				v.byteA=0x20;
				h=1;		
			}	
//			C2CMR=0x21;
			can2_tx(v);
		}
		if(RIGHT)
		{
			RIGHT=0;
//	   		C2TID1=INDICATOR_ID;
//			C2TFI1=4<<16;
			v.id=0x201;
			v.dlc=0x4;
	   		if(r)
			{
//				C2TDA1=INDICATOR_RIGHT_ON;
				v.byteA=0x50;
				r=0;
				l=1;		
			}
			else
			{
//				C2TDA1=INDICATOR_RIGHT_OFF;
				v.byteA=0x60;
				r=1;		
			}	
//			C2CMR=0x21;
			can2_tx(v);
		}

	   if(LEFT)
		{
	   		LEFT=0;
//	   		C2TID1=INDICATOR_ID;
//			C2TFI1=4<<16;
			v.id=0x201;
			v.dlc=0x4;
	   		if(l)
			{
//				C2TDA1=INDICATOR_LEFT_ON;
				v.byteA=0x30;
				l=0;
				r=1;		
			}
			else
			{
//				C2TDA1=INDICATOR_LEFT_OFF;
				v.byteA=0x40;
				l=1;		
			}	
//			C2CMR=0x21;
			can2_tx(v);
		}
	}
}





// NODE A //
//CAN2 v,v1,v2,v3;
//extern u8 IGNI,LEFT,RIGHT,flag;
//main()
//{
//	u16 r;
//	
//	adc_init();
//	can2_init();
//	
//	config_vic();
//	en_EINT_interrupts();
//	en_can2_interrupt();
//	
//	
//	v2.dlc=v3.dlc=1;
//	v.dlc=2;
//	v.rtr=0;
//	v.byteB=0;
//
//	while(1)
//	{
//		if(IGNI)					// if ignition started
//		{
//		uart0_tx_string("Ignition\r\n");
//			IGNI=0;
//			v.id=0x50;
//			v.byteA=0x10;
//			can2_tx(v);
//			while(1)
//			  {
//				  r=adc_read(1);				// read Ain1 P0.28
//				// vout=(r*3.3)/1023;			// formula to conv ADC into vtg
//				// temperature=(vout-0.5)/0.01;	//formula to conv. ADC output 
//		
//				  v.id=0x101;
//				  v.byteA=r;	
//				  can2_tx(v);
//				  delay_ms(100);
//		
//				  r=adc_read(2);				// read Ain1 P0.29
//				 
//				 
//				 // speed=(r/1023)*180;			// formula to conv ADC into speed
//		
//				  v.id=0x100;
//				  v.byteA=r;	
//				  can2_tx(v);
//				  delay_ms(100);
//
//				  if(IGNI)
//				  {
//				  	IGNI=0;
//					break;
//				}
//
//				if(LEFT)					// for left indicator
//				{
//					LEFT=0;
//					v2.id=0x201;
//					v2.byteA=0x30;
//					can2_tx(v2);
//				}
//
//				if(RIGHT)					// for right indicator
//				{
//					RIGHT=0;
//					v3.id=0x202;
//					v3.byteA=0x50;
//					can2_tx(v3);
//				}
//			}
//		}
//										  
//		if(LEFT)					// for left indicator
//		{
//			LEFT=0;
//			v2.id=0x201;
//			v2.byteA=0x30;
//			can2_tx(v2);
//		}
//
//		if(RIGHT)					// for right indicator
//		{
//			RIGHT=0;
//			v3.id=0x202;
//			v3.byteA=0x50;
//			can2_tx(v3);
//		}		 
//	}
//}
