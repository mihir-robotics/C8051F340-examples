/*
 * PWM_Generation.c
 *
 *  Created on: 14-Sep-2021
 *  
 */

#include "c8051F340.h"
#define SYSCLK 12000000		//Internal oscillator frequency in Hz

void main(){
	PCA0L = 0x0F;			//Load count corresponding to desired frequency = 50 KHz
	OSCICN = 0x83;			//Set internal oscillator to run at its maximum frequency
	CLKSEL = 0x00;			//Select internal oscillator as SYSCLK source
	XBR1 = 0x41;			//Route CEX0 to P2.3, Enable cross-bar and weak pull-up

	P2MDOUT = 0x08;			//Set CEX0(P2.3) to push-pull
	P0SKIP = 0xFF;			//Skip Port 0
	P1SKIP = 0xFF;			//Skip Port 1
	P2SKIP = 0x07;			//Skip lower three pins of Port 2 as output is required on P2.3

	while(1){
		PCA0MD = 0x08;					//Use SYSCLK as time base
		PCA0CPM0 = 0x42;				//Module 0 = 8-bit PWM Mode
		PCA0CPH0 = 256 - (256*0.50);	//Configure initial PWM duty cycle = 50%
		CR = 1;							//Start PCA counter
	}
}
