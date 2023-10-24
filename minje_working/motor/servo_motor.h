#pragma once

#include <wiringPi.h>

#define motor_pin 12

void init_motor();
void angle(int status, int value);

