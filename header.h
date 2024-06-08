/*----------Header files declarations-----------*/
#include<LPC21XX.H>
#include<string.h>

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

/*----------LCD functions-----------*/
extern void lcd_data(unsigned char);
extern void lcd_cmd(unsigned char);
extern void lcd_init(void);
extern void lcd_string(signed char *);
extern void lcd_cgram(void);
extern void lcd_atoi(int);
extern void lcd_atof(float);

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
extern void config_vic(void);
