#include"header.h"
extern CAN2 v;


//void can2_init(void)
//{
//  	PINSEL1|=0X00014000;
//	VPBDIV=1;
//	C2MOD=0X1;
//	AFMR=0X2;
//	C2BTR=0X001C001D;
//	C2MOD=0;
//}



/* can2_driver.c */

#define TCS2 ((C2GSR>>3)&1)
#define RBS2 (C2GSR&1)

u32 *ptr=(u32 *)0xE0038000;		   // starting address of AFMR RAM 

void can2_init(void)
{
	PINSEL1|=0x00014000;
	VPBDIV=1;						// PCLK=60MHz
	C2MOD=1;
	C2BTR=0x001C001D;			 	// 125 kbps baudrate

	// AFMR=2;						// select reset mode
	// AFMR Settings - Identifiers
	ptr[0]=0x20502100;				// ID 0x50   0x100      CAN2 -> 0010 0000 0101 0000 0010 0001 0000 0000   
	ptr[1]=0x21012201;				// ID 0x101  0x200      CAN2 -> 0010 0001 0000 0001 0010 0010 0000 0001
	ptr[2]=0x22021000;				// ID 0x201             CAN2 -> 0010 0010 0000 0010 0001 0000 0000 0000

	// FOR INI scripting settings
//	ptr[0]=0x40504100;				// ID 0x50   0x100      CAN2 -> 0100 0000 0101 0000 0100 0001 0000 0000   
//	ptr[1]=0x41014201;				// ID 0x101  0x200      CAN2 -> 0100 0001 0000 0001 0100 0010 0000 0001
//	ptr[2]=0x42021000;				// ID 0x201             CAN2 -> 0100 0010 0000 0010 0001 0000 0000 0000   

	SFF_sa=0;
	SFF_GRP_sa=EFF_sa=EFF_GRP_sa=ENDofTable=0xc;				
	AFMR=0;						// Enable AF Settings
	C2MOD=0;					// Cancel Reset Mode
}

void can2_tx(CAN2 v)
{
	C2TID1=v.id;
	C2TFI1=(v.dlc<<16);			// set dlc

	if(v.rtr==0)				// if dataframe
	{
		C2TDA1=v.byteA;
		C2TDB1=v.byteB;
	}
	else						// if remote frame
		C2TFI1|=(1<<30);		// rtr

	C2CMR=0x21;				// start transmission and select tx buff 1

	while(TCS2==0);
}

void can2_rx(CAN2 *ptr)
{
while(RBS2==0);
ptr->id=C2RID;
ptr->dlc=(C2RFS>>16)&0x0F;
ptr->rtr=(C2RFS>>30)&1;
if(ptr->rtr==0)	 					// if dataframe
	{
	 ptr->byteA=C2RDA;
	 ptr->byteB=C2RDB;
	}
	C2CMR=(1<<2);					// release Rx Buffer
}

