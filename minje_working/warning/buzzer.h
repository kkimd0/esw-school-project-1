#pragma once

#include <wiringPi.h>
#include "3colorLed.h"

#define RAS_CLOCK 19
#define BUZZER_PIN 13
#define NOTE_D6 1174
#define NOTE_D4 293
#define NOTE_G5 783
#define DUTY_CYCLE 0.5
#define MICROSECOND 1000000

void init_buzzer();
void setNote();
void frontWarningSound();
void sideLaneWarningSound();