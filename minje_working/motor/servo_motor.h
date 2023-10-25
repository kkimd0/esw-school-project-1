#ifndef __SERVO_MOTOR_H__
#include <wiringPi.h>
#define __SERVO_MOTOR_H__

#define MOTOR_PIN 12

void init_motor();
void setServo();
void angle(int status, int value);

#endif
