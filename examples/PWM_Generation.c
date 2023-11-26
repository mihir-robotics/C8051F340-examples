/*
 * PWM_Generation.c
 *
 *  Created on: 14-Sep-2021
 *  
 */

// Standard 8051 Library
#include "c8051F340.h"

//Internal oscillator frequency is 12 MHz
#define SYSCLK 12000000		

// Main
void main(){
	
	//Load count corresponding to desired frequency = 50 KHz
	PCA0L = 0x0F;		
	
	//Set internal oscillator to run at its maximum frequency	
	OSCICN = 0x83;			
	
	//Select internal oscillator as SYSCLK source
	CLKSEL = 0x00;			
	
	//Route CEX0 to P2.3, Enable cross-bar and weak pull-up
	XBR1 = 0x41;			

	//Set CEX0(P2.3) to push-pull
	P2MDOUT = 0x08;			
	//Skip Port 0
	P0SKIP = 0xFF;			
	//Skip Port 1
	P1SKIP = 0xFF;			
	//Skip lower three pins of Port 2 as output is required on P2.3
	P2SKIP = 0x07;			

	while(1){
		//Use SYSCLK as time base
		PCA0MD = 0x08;					
		
		//Module 0 = 8-bit PWM Mode
		PCA0CPM0 = 0x42;				
		
		//Configure initial PWM duty cycle = 50%
		PCA0CPH0 = 256 - (256*0.50);	
		
		//Start PCA counter
		CR = 1;							
	}
}
