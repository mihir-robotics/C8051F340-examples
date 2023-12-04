/*
 * ADC_Program.c
 *  Created on: 07-Sep-2021
 */

// 8051 Library
#include "c8051F340.h"

// System Clock
#define SYSCLK 12000000

// Delay Function
void delayMs(unsigned int Ms){
	unsigned int i,j;
	for(i = 0; i < Ms;i++){
		for(j=0;j<100;j++);
	}
}

// Main
void main(){

	//System Clock 12MHz
	OSCICN = 0x83;

	//Enable Cross-bar
	XBR1 = 0x40;		
	
	//P4 LED's connected make o/p
	P4MDOUT = 0xff;		
	
	//P2.5 Analog Input
	P2MDIN = 0xdf;		
	
	//Skip P2.5
	P2SKIP = 0x20;		

	//Set VDD as reference voltage for ADC
	REF0CN = 0x08;

	//P2.5 as ANIP+
	AMX0P = 0x04;		
	
	//Connect ANIP- to GND for single ended ADC
	AMX0N = 0x1f;		

	ADC0CF = (((SYSCLK/30000000)-1)<<3);
	
	//Enable ADC0
	AD0EN = 1;
	//Give SOC			
	AD0BUSY = 1;		

	//ADC0CN^AD0BUSY==1; Monitor EOC
	while(AD0BUSY == 1){	
		//wait for EOC
	}

	//Display 10-bit A/D value on LED
	P4 = ~ADC0L;		
	delayMs(100);
	
	P4 = ~ADC0H;
	delayMs(100);

	while(1);
}










































