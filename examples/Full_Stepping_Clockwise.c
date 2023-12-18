/*
 * Full_Stepping_Clockwise.c
 *  Created on: 29-Aug-2021
 */

// c8051F340 Library
#include "c8051f340.h"

// Function prototype
void DelayMs(unsigned int Ms);

// Main()
void main(){

	// Enable Cross-bar
	XBR1 = 0X40;

	// Set Port 4 as output
	P4MDOUT = 0XFF;

	// Full Stepping routine (Clockwise)
	while(1){
		P4 = 0X0A;
		DelayMs(10);
		P4 = 0X88;
		DelayMs(10);
		P4 = 0XA0;
		DelayMs(10);
		P4 = 0X22;
		DelayMs(10);
	}
}

// Software based delay
void DelayMs(unsigned int Ms){
	unsigned int n;
	unsigned int i;
	// Loop run "Ms" times
	for(n=0;n<Ms;n++){
		// Runs 65 NOP commands to create delay
		for(i=0;i<65;i++);
	}
}


