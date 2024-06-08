/*----------Header files declarations-----------*/
#include<LPC21XX.H>

/*----------Function declarations-----------*/

/*----------Defining datatypes shortcuts-----------*/
typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed int s32;
typedef unsigned int u32;

/*----------Delay functions-----------*/
extern void delay_sec(unsigned int);
extern void delay_ms(unsigned int);

/*********ADC FUNCTIONS*********/
extern void adc_init(void);
extern u16 adc_read(u8);

/*************CAN2*****************/
typedef struct CAN2_MSG
{
u32 id,byteA,byteB;
u8 dlc,rtr;
}CAN2;

extern void can2_rx(CAN2 *);
extern void can2_tx(CAN2);
extern void can2_init(void);

// INTERRUPTS
/********* CAN2 Interrupt FUNCTIONS*********/
void en_can2_interrupt(void);

/*********  PROJECT - DASHBOARD Implemenation using CAN Protocol *********/
extern void en_EINT_interrupts(void);
extern void config_vic(void);

