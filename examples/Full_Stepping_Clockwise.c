/*
 * Full_Stepping_Clockwise.c
 *
 *  Created on: 29-Aug-2021
 *      Author: Mihir Kulkarni PA-13 T-24
 */
#include "c8051f340.h"
void DelayMs(unsigned int Ms);
void main(){

	XBR1 = 0X40;
	P4MDOUT = 0XFF;

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

void DelayMs(unsigned int Ms){
	unsigned int n;
	unsigned int i;
	for(n=0;n<Ms;n++){
		for(i=0;i<65;i++);
	}
}


