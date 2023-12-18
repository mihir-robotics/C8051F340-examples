/*
 * Half_Stepping_Clockwise.c
 *  Created on: 29-Aug-2021
 */

#include "c8051f340.h"
void DelayMs(unsigned int Ms){
	unsigned int n;
	unsigned int i;
	for(n=0;n<Ms;n++){
		for(i=0;i<65;i++);
	}
}

void main(){

	int i;
	char halfStep_clockwise[]={0X02,0X0A,0X08,0X88,0X80,0XA0,0X20,0X22};
	XBR1 = 0X40;
	P4MDOUT = 0XFF;
	while(1){
		for(i=0;i<=8;i++)
		{
			P4 = halfStep_clockwise[i];
			DelayMs(10);
		}
	}
}

