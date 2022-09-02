#include "../includes/lcd.h"

//lcd_init
lcd::lcd(){
	// Initialise display

	this->fd = wiringPiI2CSetup(I2C_ADDR);
	SendDatatoPins(0x33, LCD_CMD); // Initialise
	SendDatatoPins(0x32, LCD_CMD); // Initialise
	SendDatatoPins(0x06, LCD_CMD); // Cursor move direction
	SendDatatoPins(0x0C, LCD_CMD); // 0x0F On, Blink Off
	SendDatatoPins(0x28, LCD_CMD); // Data length, number of lines, font size
	SendDatatoPins(0x01, LCD_CMD); // Clear display
	delayMicroseconds(500);
}

//lcd_byte
void lcd::SendDatatoPins(int bits, int mode){

	// bits = the data
	// mode = 1 for data, 0 for command
	int bits_high;
	int bits_low;
	// uses the two half byte writes to LCD
	bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
	bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

	wiringPiI2CReadReg8(this->fd, bits_high);
	this->lcd_toggle_enable(bits_high);

	wiringPiI2CReadReg8(this->fd, bits_low);
	this->lcd_toggle_enable(bits_low);
}

//lcdLoc
void lcd::cursorAtStart(int line){
	
	SendDatatoPins(line, LCD_CMD);
}

void lcd::typeln(const char *str){

	while (*str) SendDatatoPins(*(str++), LCD_CHR);
}

void lcd::lcd_toggle_enable(int bits){
	// Toggle enable pin on LCD display
	delayMicroseconds(500);
	wiringPiI2CReadReg8(fd, (bits | ENABLE));
	delayMicroseconds(500);
	wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
	delayMicroseconds(500);
}

void lcd::WriteOnLcd(bool line2,const char *str){
	if (line2){
		this->cursorAtStart(LINE2);
		this->typeln(str);
		return;
	}
	this->cursorAtStart(LINE1);
	this->typeln(str);
}

void lcd::WriteInt(bool line2,const char *str,int myInt){
	if (line2) this->cursorAtStart(LINE2);
	if (!line2)this->cursorAtStart(LINE1);
	this->typeln(str);

	char buffer[20];
	sprintf(buffer, "%d",  myInt);
	this->typeln(buffer);
}

void lcd::WriteFloat(bool begin,bool line2,const char *str,float myFloat){
	
	if (begin){
		if (line2) this->cursorAtStart(LINE2);
		if (!line2)this->cursorAtStart(LINE1);
	}
	this->typeln(str);


	char buffer[20];
	sprintf(buffer, "%4.2f",  myFloat);
	this->typeln(buffer);
}

//ClrLcd
void lcd::moveCursor(){
	this->lcd_byte(0x01, LCD_CMD);
	this->lcd_byte(0x02, LCD_CMD);
}

void lcd::lcd_byte(int bits, int mode){

	//Send byte to data pins
	// bits = the data
	// mode = 1 for data, 0 for command
	int bits_high;
	int bits_low;
	// uses the two half byte writes to LCD
	bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
	bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

	// High bits
	wiringPiI2CReadReg8(fd, bits_high);
	this->lcd_toggle_enable(bits_high);

	// Low bits
	wiringPiI2CReadReg8(fd, bits_low);
	this->lcd_toggle_enable(bits_low);
}