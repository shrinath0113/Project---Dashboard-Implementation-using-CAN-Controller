/* CAN2 interrupt handler */
#include"header.h"
extern u8 flag;
extern CAN2 v;

void CAN2_RX_Handler(void) __irq
{
	v.id=C2RID;
	v.dlc=(C2RFS>>16)&0xF;
	v.rtr=(C2RFS>>30)&1;
	if(v.rtr==0)					// if dataframe
	{
		v.byteA=C2RDA;
		v.byteB=C2RDB;
	}
	C2CMR=(1<<2);					// Release RxBuf (vimp)
	flag=1;
	VICVectAddr=0;					// to finish the isr
}

void en_can2_interrupt(void)
{
	C2IER=1;						// Enable CAN2 RX Interrupt
}

void config_vic(void)
{
	VICIntSelect=0;
	VICVectCntl13=27|(1<<5);
	VICVectAddr13=(u32)CAN2_RX_Handler;
	VICIntEnable|=1<<27;
}
