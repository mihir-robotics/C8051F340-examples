/*
 * LCD_Program.c
 *  Created on: 14-Aug-2021
 */

//Include the header file for C8051F340 Micro-controller
#include "c8051F340.h"

//Function Prototypes/Signatures
void DelayMs(unsigned int Ms);					//Delay Routine Function
void Write_Command_Lcd(unsigned char Command);	//Function to send Command to LCD
void Write_Data_Lcd(unsigned char Character);	//Function to send Character to LCD


sbit LCD_RS = P1^5;				//Register Select of LCD is assigned to P1.5
sbit LCD_RW = P1^6;				//Read/Write of LCD is assigned to P1.6
sbit LCD_EN = P1^7;				//Enable pin is assigned to P1.7

void main(){

	XBR1 = 0x40;				//Enable Cross-bar
	P2MDOUT = 0xFF;				//Set P2 as output port
	P1MDOUT = 0xE0;				//Set P1.5,P1.6,P1.7 as output pins

	Write_Command_Lcd(0x38);	//2 lines and 5x7 Matrix
	DelayMs(50);

	Write_Command_Lcd(0x01);	//Clear display screen
	DelayMs(50);

	Write_Command_Lcd(0x0C);	//Display ON, Cursor OFF
	DelayMs(50);

	Write_Command_Lcd(0x80);	//Force cursor to beginning of 1st line
	DelayMs(50);

	Write_Data_Lcd('W');		//Call Data Routine
	DelayMs(50);

	Write_Data_Lcd('P');
	DelayMs(50);

	Write_Data_Lcd('U');
	DelayMs(50);

	while(1);
}

//Delay routine function which takes miliseconds as input
void DelayMs(unsigned int Ms){
	unsigned int n;
	unsigned int i;

	for(n=0; n < Ms; n++){
		for(i=0; i < 65; i++);
	}
}

//Function to write command to LCD
void Write_Command_Lcd(unsigned char Command){
	LCD_RS = 0;					//RS value is set to 0 to denote that command is being sent
	LCD_RW = 0;					//RW value is set to 0 as we are writing to LCD
	P2 = Command;
	LCD_EN = 1;					//EN pin High -> Low
	DelayMs(15);
	LCD_EN = 0;
}

//Function to send Character to LCD
void Write_Data_Lcd(unsigned char Character){
	LCD_RS = 1;					//RS value is set to 1 as actual data is being sent.
	LCD_RW = 0;					//RW value is set to 0 as we are writing to LCD
	P2 = Character;
	LCD_EN = 1;					//EN pin High -> Low
	DelayMs(15);
	LCD_EN = 0;
}

















