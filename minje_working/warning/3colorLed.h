#pragma once

#include <wiringPi.h>

#define Red_pin 22
#define Green_pin 27
#define Blue_pin 17

void init_3colorLed();
void turnRed();
void offRed();
void turnGreen();
void offGreen();
void turnBlue();
void offBlue();