/*
 * LED_Relay_Buzzer.c
 *
 *  Created on: 10-Aug-2021
 *      Author: Mihir Kulkarni PA-13 T-24
 */

#include "c8051F340.h"
#define LED P4

sbit KEY1 = P1^0;
sbit KEY2 = P1^1;
sbit RELAY = P1^4;
sbit BUZZER = P3^3;

void main(){

	XBR1 = 0x40;		//Crossbar enabled
	P1MDIN = 0x03;		//Pins 1.0 and 1.1 configured as Digital Inputs
	P1MDOUT = 0x10;		//P1.4 pins configured as Output

	P4MDOUT = 0xFF;		//P4 pins configured as Output
	P3MDOUT = 0x08;		//P3.3 pins configured as Output

	while(1){
		if(KEY1==0){		//Key1 Pressed
			while(1){		//LED,Relay,Buzzer ON
				LED = 0x00;
				RELAY = 0;
				BUZZER = 1;
				if(KEY2==0){
					break;
				}
			}
		}
		if(KEY2==0){		//Key2 Pressed
			while(1){		//LED,Relay,Buzzer OFF
				LED = 0xFF;
				RELAY = 1;
				BUZZER = 0;
				if(KEY1==0){
					break;
				}
			}
		}
	}
}
