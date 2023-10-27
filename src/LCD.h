#ifndef __LCD_H__
#define __LCD_H__

#include "sensor.h"

// Define some device constants
#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

#define LCD_BACKLIGHT   0x08  // On
// LCD_BACKLIGHT = 0x00  # Off

#define ENABLE  0b00000100 // Enable bit
// Define some device parameters
#define I2C_ADDR   0x27 // I2C device address

void init_LCD(void);
void lcd_byte(int32_t bits, int32_t mode);
void lcd_toggle_enable(int32_t bits);

// added by Lewis
void lcdLoc(int32_t line); //move cursor
void ClrLcd(void); // clr LCD return home
void typeln(const char *s);

void printLCD(const char *s_Line1, const char *s_Line2);
void usePrint_LCD(uint32_t selectString);

#endif
