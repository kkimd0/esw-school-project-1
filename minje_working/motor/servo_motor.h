#ifndef __SERVO_MOTOR_H__
#include <wiringPi.h>
#define __SERVO_MOTOR_H__

#define MOTOR_PIN 12
#define MOTOR_PULSE 0.6

void init_motor();
void setServo();
int setAngleFast(int angle);
int setAngleSlow(int start, int end);
int IR_Window_Up(int currentAngle);
void IR_Window_Down(int currentAngle);
#endif
