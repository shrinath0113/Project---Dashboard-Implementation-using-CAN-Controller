// LCD driver for 4-bit 
/*-------------Rhydolabz Board-----------------*/

#include<LPC21XX.H>
#include "header.h"
#define RS (1<<17)
#define	RW (1<<18)
#define EN (1<<19)

#define PIN 0x00FE0000

void lcd_data(u8 data){
	u32 temp;
	IOCLR1=PIN;
	temp=(data & 0xF0)<<16;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;

	IOCLR1=PIN;
	temp=(data & 0x0F)<<20;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
}

void lcd_cmd(u8 cmd){
	u32 temp;
	IOCLR1=PIN;
	temp=(cmd & 0xF0)<<16;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;

	IOCLR1=PIN;
	temp=(cmd & 0x0F)<<20;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
}

				 
void lcd_init(void)
{
IODIR1=PIN;
IOCLR1=EN;
PINSEL2=0x0;
lcd_cmd(0x01);
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x0E);
lcd_cmd(0x01);
}


void lcd_string(s8 *ptr)
{
	while(*ptr!=0)
	lcd_data(*ptr++);
}


void lcd_cgram(void)
{
 	u8 a1[8]={0x00,0x00,0x00,0x1F,0x1F,0x1F,0x00,0x00};
	u8 a2[8]={0x00,0x10,0x18,0x1C,0x1E,0x1C,0x18,0x10};
	u8 a3[8]={0x00,0x01,0x03,0x07,0x0F,0x07,0x03,0x01};
	u8 a4[8]={0x03,0x05,0x09,0x11,0x11,0x09,0x05,0x03};
	u8 a5[8]={0x1E,0x00,0x1E,0x00,0x1E,0x00,0x1E,0x00};
	int i;
	lcd_cmd(0x40);
	for(i=0;i<8;i++)
	{
	 	lcd_data(a1[i]);
	}
	lcd_cmd(0x40+8);
	for(i=0;i<8;i++)
	{
	 	lcd_data(a2[i]);
	}
	lcd_cmd(0x40+16);
	for(i=0;i<8;i++)
	{
	 	lcd_data(a3[i]);
	}
	lcd_cmd(0x40+24);
	for(i=0;i<8;i++)
	{
	 	lcd_data(a4[i]);
	}
	lcd_cmd(0x40+32);
	for(i=0;i<8;i++)
	{
	 	lcd_data(a5[i]);
	}
}

void lcd_atoi(s32 num)
{
s32 i=0;
char a[10];

	if(num==0){
	lcd_data('0');
	return;
	}
	if(num < 0)
	{
	num=-num;
	lcd_data('-');
	}
	while(num>0){
	a[i]=(num%10)+48;
	i++;
	num/=10;
	}
	for(i--;i>=0;i--)
	lcd_data(a[i]);	
}

void lcd_atof(float f)
{
int temp,temp1,i,l;
char a[16];
	if(f==0)
	{
	lcd_string("0.000000");
	return;
	}

	if(f<0)
	{
	lcd_data('-');
	f=-f;
	}

	temp=f;
	if(temp==0)
	{
	lcd_data('0');
	}
	else
	{
		for(l=0,temp1=temp;temp1;temp1=temp1/10,l++);
		l--;

		for(temp1=temp,i=0;temp1;temp1=temp1/10,i++)
		{
			a[i]=(temp1%10)+48;
		}

		for(i=l;i>=0;i--)
		{
			lcd_data(a[i]);
		}
	}

	lcd_data('.');

	temp=(f-temp)*1000000;
	if(temp==0)
	{
//		lcd_string("000000");
		lcd_string("00");
	}
	else
	{
		for(i=0;temp;temp=temp/10,i++)
		{
			a[i]=(temp%10)+48;
		}
//		for(i=5;i>=0;i--)
//		{
//			lcd_data(a[i]);
//		}
		for(i=1;i>=0;i--)
		{
			lcd_data(a[i]);
		}
	}
}



