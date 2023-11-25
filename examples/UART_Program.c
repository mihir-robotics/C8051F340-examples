/*
 * UART_Program.c
 *
 *  Created on: 21-Sep-2021
 *      Author: Mihir Kulkarni PA-13 T-24
 */

#include "c8051F340.h"		//C8051F340 library
#define SYSCLK 12000000		//Set value to 12MHz
#define BR_UART0 9600		//Set baud rate as 9600

void main(){
	// char ch[] = {"MIT"};

	int i;
	OSCICN = 0x83;			//Configure internal oscillator for maximum frequency (12MHz)
	XBR0 = 0x01;			//Enable UART
	XBR1 = 0x40;			//Enable Cross-bar
	P0MDOUT = 0x10;			//Pin 4 on Port 0 configured as output
	SCON0 = 0x00;

	CKCON = 0x01;
	TH1 = -(SYSCLK/BR_UART0/2/4);

	TL1 = TH1;				//Init Timer 1
	TMOD = 0x20;			//Timer 1 in 8-bit auto reload
	TR1 = 1;				//Start Timer 1
	SBUF0 = 'M';			//For single character

	while(TI0==0);
	TI0=0;

	while(1);
}
