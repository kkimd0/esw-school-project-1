#ifndef __WINDOW_OPEN_CLOSE_H__
#include <wiringPi.h>
#include "./Module_determine_tunnel/determine_tunnel.h"
#define __WINDOW_OPEN_CLOSE_H__

#define MOTOR_PIN 13
#define MOTOR_PULSE 0.6

void init_motor();
void setServo();
void setAngleFast(int angle);
void setAngleSlow(int start, int end);
#endif