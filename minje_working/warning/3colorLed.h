#ifndef __3COLORLED_H__
#define __3COLORLED_H__

#include <wiringPi.h>

#define RED_PIN 22
#define GREEN_PIN 27
#define BLUE_PIN 17

void init_3colorLed();
void turnRed();
void offRed();
void turnGreen();
void offGreen();
void turnBlue();
void offBlue();

#endif
