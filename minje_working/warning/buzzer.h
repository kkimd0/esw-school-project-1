#pragma once

#include <wiringPi.h>
#include "3colorLed.h"

#define BUZZER_PIN 13
#define NOTE_D6 1174
#define DUTY_CYCLE 0.5
#define MICROSECOND 1000000

void init_buzzer();
void setWarningSound();
void warningSound();