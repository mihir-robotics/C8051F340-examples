/*
 * ADC_Program.c
 *
 *  Created on: 07-Sep-2021
 *      Author: Mihir Kulkarni PA-13 T-24
 */

//Program for ADC
#include "c8051F340.h"
#define SYSCLK 12000000

void delayMs(unsigned int Ms){
	unsigned int i,j;
	for(i = 0; i < Ms;i++){
		for(j=0;j<100;j++);
	}
}

void main(){

	OSCICN = 0x83;		//System Clock 12MHz
	XBR1 = 0x40;		//Enable Cross-bar
	P4MDOUT = 0xff;		//P4 LED's connected make o/p
	P2MDIN = 0xdf;		//P2.5 Analog Input
	P2SKIP = 0x20;		//Skip P2.5

	REF0CN = 0x08;		//Set VDD as reference voltage for ADC
	AMX0P = 0x04;		//P2.5 as ANIP+
	AMX0N = 0x1f;		//Connect ANIP- to GND for single ended ADC

	ADC0CF = (((SYSCLK/30000000)-1)<<3);
	AD0EN = 1;			//Enable ADC0
	AD0BUSY = 1;		//Give SOC

	while(AD0BUSY == 1){	//ADC0CN^AD0BUSY==1; Monitor EOC
		//wait for EOC
	}
	P4 = ~ADC0L;		//Display 10-bit A/D value on LED
	delayMs(100);
	P4 = ~ADC0H;
	delayMs(100);

	while(1);
}










































