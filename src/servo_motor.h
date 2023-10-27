#ifndef __SERVO_MOTOR_H__
#define __SERVO_MOTOR_H__
#include <wiringPi.h>
#include "sensor.h"

#define MOTOR_PIN 12
#define MOTOR_PULSE 0.6

void init_motor();
void setServo();
int setAngleFast(int angle);
int setAngleSlow(int start, int end);

void *thread_window_up();
void *thread_window_down();
void *thread_window_origin();

void IR_Window_Up();
void IR_Window_Down();

static uint16_t now_angle;
static uint16_t saved_angle;


#endif
