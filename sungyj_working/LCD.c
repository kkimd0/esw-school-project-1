/*
  [상태 출력 LCD 모듈]
  void usePrint_LCD()의 인자에 따라 LCD 출력 선택 (500 ms 주기)

  -1 이면, "Warning!!", "Warning!!" 출력
  0 이면, "In Tunnel", "Auto mode" 출력
  1 이면, "In Tunnel", "Manual mode" 출력
  2 이면, "OutSide Tunnel", "Manual mode" 출력
  3 이면, "OutSide Tunnel", "Auto mode" 출력
*/

#include "LCD.h"

int main()   {

  if (wiringPiSetup () == -1) exit (1);

  fd = wiringPiI2CSetup(I2C_ADDR);

  lcd_init(); // setup LCD
  
  while (1)   {
    usePrint_LCD(-1);
    usePrint_LCD(0);
    usePrint_LCD(1);
    usePrint_LCD(2);
    usePrint_LCD(3);
  }

  return 0;
}



void lcd_byte(int32_t bits, int32_t mode)   {

  //Send byte to data pins
  // bits = the data
  // mode = 1 for data, 0 for command
  int32_t bits_high;
  int32_t bits_low;
  // uses the two half byte writes to LCD
  bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
  bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

  // High bits
  wiringPiI2CReadReg8(fd, bits_high);
  lcd_toggle_enable(bits_high);

  // Low bits
  wiringPiI2CReadReg8(fd, bits_low);
  lcd_toggle_enable(bits_low);
}

void lcd_toggle_enable(int32_t bits)   {
  // Toggle enable pin on LCD display
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits | ENABLE));
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
  delayMicroseconds(500);
}

void lcd_init()   {
  // Initialise display
  lcd_byte(0x33, LCD_CMD); // Initialise
  lcd_byte(0x32, LCD_CMD); // Initialise
  lcd_byte(0x06, LCD_CMD); // Cursor move direction
  lcd_byte(0x0C, LCD_CMD); // 0x0F On, Blink Off
  lcd_byte(0x28, LCD_CMD); // Data length, number of lines, font size
  lcd_byte(0x01, LCD_CMD); // Clear display
  delayMicroseconds(500);
}

// clr lcd go home loc 0x80
void ClrLcd(void)   {
  lcd_byte(0x01, LCD_CMD);
  lcd_byte(0x02, LCD_CMD);
}

// go to location on LCD
void lcdLoc(int32_t line)   {
  lcd_byte(line, LCD_CMD);
}

// this allows use of any size string
void typeln(const char *s)   {
  while ( *s ) lcd_byte(*(s++), LCD_CHR);
}


void printLCD(const char *s_Line1, const char *s_Line2)  {
    ClrLcd();
    lcdLoc(LINE1);
    typeln(s_Line1);
    lcdLoc(LINE2);
    typeln(s_Line2);
    delay(500);
}

void usePrint_LCD(int32_t selectString) {
  switch (selectString) {
    case -1 :
      printLCD("Warning!!", "Warning!!");
      break;
    case 0 :
      printLCD("In Tunnel", "Auto mode");
      break;
    case 1 :
      printLCD("In Tunnel", "Manual mode");
      break;
    case 2 :
      printLCD("OutSide Tunnel", "Manual mode");
      break;
    case 3 :
      printLCD("OutSide Tunnel", "Auto mode");
      break;
    default :
      break;
  }
}