/*
 * Full_Stepping_Anticlockwise.c
 *  Created on: 29-Aug-2021
 */

// Standard Library
#include "c8051f340.h"

// Function prototype for delay function
void DelayMs(unsigned int Ms);

// Main()
void main(){
	// Enable Cross-bar
	XBR1 = 0X40;
	// Configure Port 4 as output
	P4MDOUT = 0XFF;

	// Full Stepping (Anticlockwise) routine for Motor
	while(1){
		P4 = 0X22;
		DelayMs(10);
		P4 = 0XA0;
		DelayMs(10);
		P4 = 0X88;
		DelayMs(10);
		P4 = 0X0A;
		DelayMs(10);
	}
}

// DelayMs (Software based delay)
void DelayMs(unsigned int Ms){
	unsigned int n;
	unsigned int i;
	// loop runs Ms times to create req. delay
	for(n=0;n<Ms;n++){
		// Create delay by executing 65 'no-operation' commands (i.e empty loop)
		for(i=0;i<65;i++);
	}
}
