/*
 * MA_RFID_CaseStudy.c

 *
 */

// Program to interface EM-18 RFID reader and 16*2 LCD with C8051F340
// Objective of program is to take RFID card number from reader and display data on LCD

#include "c8051F340.h"		//C8051F340 library
#define SYSCLK 12000000		//Set value to 12MHz
#define BR_UART0 9600		//Set baud rate as 9600 as EM-18 uses same baudrate


//Function Prototypes/Signatures that are used throughout

void delayMS(unsigned int MS);				//Delay Routine
void writeCommand(unsigned char Command);	//Function to send commands to LCD
void writeData(unsigned char Character);	//Function to send data to LCD
char readTX(void);							//Function to read character from EM-18

sbit LCD_RS = P1^5;		//Register Select of LCD is assigned to P1.5
sbit LCD_RW = P1^6;		//Read/Write of LCD is assigned to P1.6
sbit LCD_EN = P1^7;		//Enable pin is assigned to P1.7

int i=0;
char count = 0;			//Variable to keep count of characters read by readTX()
char card_number[12];	//Array to hold 12-character number of RFID card

unsigned char commands[4]={0x38,0x01,0x0C,0x08};	/*Array to store list of LCD commands
 	 	 	 	 	 	 	 	 	 	 	 	 	 	0x38 -> 2 lines and 5x7 matrix
 	 	 	 	 	 	 	 	 	 	 	 	 	 	0x01 -> Clear display screen
 	 	 	 	 	 	 	 	 	 	 	 	 	 	0x0C ->	Display ON, Cursor OFF
 	 	 	 	 	 	 	 	 	 	 	 	 	 	0x80 -> Force Cursor to beginning of 1st line.*/

void main(){

	OSCICN = 0x83;		//Configure internal oscillator for max freq. (12 MHz)
	XBR0 = 0x01;		//Enable UART
	XBR1 = 0x40;		//Enable Cross-bar

	P1MDOUT = 0xE0;		//Set pins 5,6,7 as output pins
	P2MDOUT = 0xFF;		//Set P2 as output port
	P3MDIN =  0xFE;		//Set Pin 3.0 as input
	SCON0 = 0x08;		//Serial Control register is given command to enable UART receiver (REN0 bit set '1')

	CKCON = 0x01;
	TH1 = -(SYSCLK/BR_UART0/2/4);	//Timer value for 9600 bps
	TL1 = TH1;						//Init Timer 1
	TMOD = 0x20;					//Timer 1 in 8-bit auto-reload
	TR1 = 1;							//Start Timer 1


	for(i=0;i<4;i++){
		writeCommand(commands[i]);	//Call function to write commands to LCD
		delayMS(50);				//Call delay routine
	}

	//As code is running continously, while loop is used
	while(1){
		count = 0;
		writeCommand(0x80);			//Force cursor to beginning of first line

		while(count < 12){
			card_number[count]=readTX();	//Receive data from EM-18 and store it in array
			count++;						//Increment counter variable by one.
		}

		for(i=0;i<12;i++){
			writeData(card_number[i]);		//Send data to LCD one character at a time.
			delayMS(50);
		}

		delayMS(50);

	}

}

//Delay routine function which takes milliseconds as input.
void delayMS(unsigned int MS){
	unsigned int n;
	unsigned int i;

	for(n=0;n<MS;n++){
		for(i=0;i<65;i++);
	}
}

//Function to write commands to LCD
void writeCommand(unsigned char Command){
	LCD_RS = 0;		//RS value is set to 0 to denote command mode
	LCD_RW = 0;		//RW value is 0 as write mode is selected
	P2 = Command;
	LCD_EN = 1;		//EN pin HIGH -> LOW
	delayMS(15);
	LCD_EN = 0;
}

void writeData(unsigned char Character){
	LCD_RS = 1;		//RS value is set to 1 as actual data is being sent
	LCD_RW = 0;		//RW value is 0 as we are writing to LCD
	P2 = Character;
	LCD_EN = 1;		//EN pin HIGH -> LOW
	delayMS(15);
	LCD_EN = 0;
}

//Function to read single character from EM-18
char readTX(void){
	char ch;
	while(TI0==0);	//Wait till TI0 becomes HIGH, i.e Card is swiped
	TI0 = 0;
	ch = SBUF0;		//Assign value stored in SBU0 register to ch
	return ch; 		//Return received character
}










