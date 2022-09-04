#ifndef LCD_H
#define LCD_H

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>


#define I2C_ADDR   0x27 // I2C device address

#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

#define LCD_BACKLIGHT   0x08  // On

#define ENABLE  0b00000100 



class lcd{
private:
	int fd;  // seen by all subroutines

	void lcd_byte(int bits, int mode);
	void cursorAtStart(int line);
	void moveCursor();
	void typeln(const char *str);
	void lcd_toggle_enable(int bits);

public:
	lcd();
	void WriteOnLcd(bool line2,const char *str);
	void WriteInt(bool begin,bool line2,const char *str,int myInt);
	void WriteFloat(bool begin,bool line2,const char *str,float myFloat);

};

#endif //LCD_H