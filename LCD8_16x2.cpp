//LCD Functions Developed by LIGO GEORGE @ electroSome.com
//original files : https://electrosome.com/interfacing-lcd-atmega32-microcontroller-atmel-studio/
/*Additional develop made by Mohammed Essam Mahran (mhran9333@gmail.com)*/
//This driver is for 16x2 LCD (Used in 8 Pins Mode)
#define F_CPU 8000000UL // 8 MHz clock speed

#include "LCD8_16x2.h"


#define RS 0x80
#define RW 0x40
#define EN 0x20

void lcd8_16x2::_delay_ms(unsigned short n){

	n*=500;

	while(n)
		n--;

}

void lcd8_16x2::ControlPinChange(unsigned char Control_Pin, unsigned char State) //Change LCD Data pin state (HIGH or LOW)
{
	switch (State)
	{
	case 1:
	{
		contolByte |= Control_Pin;
	}
		break;

	case 0:
	{
		contolByte &= ~Control_Pin;
	}
		break;
	}

	exp->writeB(contolByte);
}



void lcd8_16x2::LCD8_Port(unsigned char a)	//LCD Data pins masking (sending data or command to LCD from AVR)
{
	exp->writeA(a);
}

void lcd8_16x2::LCD8_Command(unsigned char Command)	//Send command from AVR to LCD
{
	ControlPinChange(RS, 0);             // => RS = 0
	LCD8_Port(Command);            					  //Data transfer
	ControlPinChange(EN, 1);             // => E = 1
	_delay_ms(1);
	ControlPinChange(EN, 0);             // => E = 0
	_delay_ms(1);
}


//void lcd8_16x2::Set_Cursor(unsigned char Row, unsigned char Column) //Set cursor of LCD depending on Row and Column location (16X2 LCD) 16 columns , 2 rows
//{
//	if (Row == 1)
//		LCD8_Command(0x80 + Column - 1);
//	else if (Row == 2)
//		LCD8_Command(0xC0 + Column - 1);
//}

void lcd8_16x2::Init()	//Initialize LCD (This function is first called in main() )
{
	ControlPinChange(RS, 0);
	ControlPinChange(EN, 0);
	_delay_ms(20);
	/*			 Reset process from datasheet 		*/
	LCD8_Command(0x30);
	_delay_ms(5);
	LCD8_Command(0x30);
	_delay_ms(1);
	LCD8_Command(0x30);
	_delay_ms(10);

	LCD8_Command(0x38);    //function set
	LCD8_Command(0x0C);    //display on,cursor off,blink off
	LCD8_Command(0x01);    //clear display
	LCD8_Command(0x06);    //entry mode, set increment

	_numlines =2;

}

void lcd8_16x2::Write_Char(unsigned char Character) 	//Write a character to LCD
{
	ControlPinChange(RS, 1);             // => RS = 1
	LCD8_Port(Character);             				  //Data transfer
	ControlPinChange(EN, 1);             // => E = 1
	_delay_ms(1);
	ControlPinChange(EN, 0);             // => E = 04
	_delay_ms(1);
}

void lcd8_16x2::Write_String(char *String)		//Write a string to LCD
{
	int i;
	for (i = 0; String[i] != '\0'; i++)
		Write_Char(String[i]);
}

void lcd8_16x2::Shift_Right()		//Shift LCD to right
{
	LCD8_Command(0x1C);
}

void lcd8_16x2::Shift_Left()	//Shift LCD to left
{
	LCD8_Command(0x18);
}

/********** high level commands, for the user! */
void lcd8_16x2::clear()
{
	LCD8_Command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero

	_delay_ms(3);

}

void lcd8_16x2::home()
{
	LCD8_Command(LCD_RETURNHOME);  // set cursor position to zero
	_delay_ms(2);  // this command takes a long time!
}

void lcd8_16x2::Set_Cursor(unsigned char col, unsigned char row)
{
  int row_offsets[4] = { 0x00, 0x40, 0x14, 0x54 };
  if ( row > _numlines ) {
    row = _numlines-1;    // we count rows starting w/0
  }

  LCD8_Command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void lcd8_16x2::noDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  LCD8_Command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void lcd8_16x2::display() {
  _displaycontrol |= LCD_DISPLAYON;
  LCD8_Command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void lcd8_16x2::noCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  LCD8_Command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void lcd8_16x2::cursor() {
  _displaycontrol |= LCD_CURSORON;
  LCD8_Command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void lcd8_16x2::noBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  LCD8_Command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void lcd8_16x2::blink() {
  _displaycontrol |= LCD_BLINKON;
  LCD8_Command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void lcd8_16x2::scrollDisplayLeft(void) {
	LCD8_Command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void lcd8_16x2::scrollDisplayRight(void) {
	LCD8_Command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void lcd8_16x2::leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  LCD8_Command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void lcd8_16x2::rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  LCD8_Command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void lcd8_16x2::autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  LCD8_Command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void lcd8_16x2::noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  LCD8_Command(LCD_ENTRYMODESET | _displaymode);
}
