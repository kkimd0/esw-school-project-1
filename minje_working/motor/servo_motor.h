#pragma once

#include <wiringPi.h>

#define MOTOR_PIN 12

void init_motor();
void setServo();
void angle(int status, int value);

