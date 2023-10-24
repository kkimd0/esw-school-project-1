#pragma once

#include <wiringPi.h>
#include "3colorLed.h"

#define buzzer_pin 18

void init_buzzer();
void setWarningSound();
void warningSound();