#include "header.h"

#define LED (7<<17)
#define OVER (1<<17)
#define LLED (1<<18)
#define RLED (1<<19)
#define BUZ (1<<21)

CAN2 v;
u8 flag;
int main()
{
	float temp;
//	float t;
	u32 speed;

	lcd_init();
	can2_init();
	en_can2_interrupt();
	config_vic();

	lcd_cgram();
	lcd_cmd(0x80);
	lcd_string("S:");
	lcd_cmd(0x88);
	lcd_string("TEMP:");
	lcd_cmd(0xC7);

	lcd_cmd(0x0C);

	lcd_data(3);

	IODIR0|=LED;
	IOSET0|=LED;

	IODIR0|=BUZ;
//	IOSET0|=BUZ;
	while(1)
	{
		if(flag)
		{
			flag=0;
		    if(v.id==0x101)
			{
				lcd_cmd(0x8D);
//				t=((v.byteA*3.3)/1023);
//				temp=(t-0.5)/0.01;
				temp=(((v.byteA*3.3)/1023)-0.5)/0.01;
				
				lcd_data(((int)temp/100)+48);
				lcd_data((((int)temp/10)%10)+48);
				lcd_data(((int)temp%10)+48);
			}
			if(v.id==0x100)
			{
				lcd_cmd(0x82);
				speed=(v.byteA*180)/1023;
				lcd_data((speed/100)+48);
				lcd_data(((speed/10)%10)+48);
				lcd_data((speed%10)+48);
				lcd_cmd(0x85);
				lcd_string("KP");
				if(speed>=120)
				{
					IOCLR0|=OVER;
					IOSET0|=BUZ;
				}
				else
				{
					IOSET0|=OVER;
					IOCLR0|=BUZ;
				}
			}
			if(v.id==0x50)
			{
				if(v.byteA==0x10)
				{
					lcd_cmd(0xC8);
				    lcd_data(4);
				}
			  	else if(v.byteA==0x20)
				{
				    lcd_cmd(0xC8);
				    lcd_data(' ');
				}
			}
			if(v.id==0x201 || v.id==0x202)
			{
				if(v.byteA==0x50)	  		// RIGHT INDICATOR ON
				{
					lcd_cmd(0xC1);
					lcd_data(' ');
					lcd_data(' ');
					lcd_cmd(0xCD);
				    lcd_data(0);
					lcd_data(1);
					
					IOCLR0|=RLED;
					IOSET0|=LLED;
				}
			  	else if(v.byteA==0x30)		// LEFT INDICATOR ON
				{
	  				lcd_cmd(0xC1);
				    lcd_data(2);
					lcd_data(0);
					lcd_cmd(0xCD);
					lcd_data(' ');
					lcd_data(' ');

					IOCLR0|=LLED;
					IOSET0|=RLED;
				}
				else if(v.byteA==0x60)		// RIGHT INDICATOR OFF
				{
	  				lcd_cmd(0xCD);
				    lcd_data(' ');
					lcd_data(' ');

					IOSET0|=RLED;
				}
				else if(v.byteA==0x40)		// LEFT INDICATOR OFF
				{
	  				lcd_cmd(0xC1);
				    lcd_data(' ');
					lcd_data(' ');

					IOSET0|=LLED;
				}
			}
	    }			
	}
}
