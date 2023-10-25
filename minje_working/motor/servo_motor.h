#ifndef __SERVO_MOTOR_H__
#include <wiringPi.h>
#define __SERVO_MOTOR_H__

#define MOTOR_PIN 12
#define MOTOR_PULSE 0.6

void init_motor();
void setServo();
void setAngleFast(int angle);
void setAngleSlow(int start, int end);
#endif
