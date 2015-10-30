//LCD Functions Developed by LIGO GEORGE @ electroSome.com
//original files : https://electrosome.com/interfacing-lcd-atmega32-microcontroller-atmel-studio/
/*Additional develop made by Mohammed Essam Mahran (mhran9333@gmail.com)*/
//This driver is for 16x2 LCD (Used in 8 Pins Mode)

#include "mcp23s17.h"

#ifndef LCD8_16x2_H_
#define LCD8_16x2_H_

//Data and control ports/pins configuration (Configured by user due to hardware connections)
#define LCD_PORT		   PORTB
#define LCD_CTRL_PORT	 PORTC

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00




class lcd8_16x2
{
public:

	mcp23s17* exp;
	uint8_t contolByte;

	void DataPinChange(unsigned char LCD_Pin, unsigned char State);				//Change LCD Data pin state (HIGH or LOW)
	void ControlPinChange(unsigned char LCD_Pin, unsigned char State);  //Change LCD Control pin state (HIGH or LOW)
	void LCD8_Port(unsigned char a);														//LCD Data pins masking (sending data or command to LCD from AVR)
	void LCD8_Command(unsigned char Command);										//Send command from AVR to LCD

	void clear();
	  void home();
	  void noDisplay();
	  void display();
	  void noBlink();
	  void blink();
	  void noCursor();
	  void cursor();
	  void scrollDisplayLeft();
	  void scrollDisplayRight();
	  void leftToRight();
	  void rightToLeft();
	  void autoscroll();
	  void noAutoscroll();


	//Clear LCD
	void Set_Cursor(unsigned char Row, unsigned char Column);		//Set cursor of LCD depending on Row and Column location (16X2 LCD) 16 columns , 2 rows
	void Init();															    		//Initialize LCD (This function is first called in main() )
	void Write_Char(unsigned char Character);							//Write a character to LCD
	void Write_String(char *String);									//Write a string to LCD
	void Shift_Right();															//Shift LCD to right
	void Shift_Left();	//Shift LCD to left
	void _delay_ms(unsigned short n);


	unsigned char _displayfunction;
	  unsigned char _displaycontrol;
	  unsigned char _displaymode;
	  unsigned char _initialized;
	  unsigned char _currline;
	  unsigned char _numlines;


};
#endif //LCD8_16x2_H_
