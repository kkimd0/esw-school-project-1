#ifndef __SERVO_MOTOR_H__
#define __SERVO_MOTOR_H__
#include <wiringPi.h>
#include "sensor.h"

#define MOTOR_PIN 16
#define PULSE 20000
#define OPENWINDOW 500
#define CLOSEWINDOW 2500
#define SET_DELAY 800

void init_servo_motor();
void setAngle(uint16_t value);

void *thread_window_up();
void *thread_window_down();
void *thread_window_origin();

void IR_Window_Up();
void IR_Window_Down();

#endif
