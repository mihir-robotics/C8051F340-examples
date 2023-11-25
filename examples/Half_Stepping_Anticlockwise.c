/*
 * Half_Stepping_Anticlockwise.c
 *
 *  Created on: 29-Aug-2021
 *      Author: Mihir Kulkarni PA-13 T-24
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
	char halfStep_antiClockwise[]={0X22,0X20,0XA0,0X80,0X88,0X08,0X0A,0X02};
	XBR1 = 0X40;
	P4MDOUT = 0XFF;
	while(1)
	{
		for(i=0;i<=8;i++)
		{
			P4 = halfStep_antiClockwise[i];
			DelayMs(10);
		}
	}
}

