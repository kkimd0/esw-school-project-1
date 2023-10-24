#pragma once

#include <wiringPi.h>
#include "3colorLed.h"

#define buzzer_pin 18

int init_buzzer(){
    
    pinMode(buzzer_pin, PWM_OUTPUT);
    pwmSetClock(19);
    pwmSetMode(PWM_MODE_MS);

    return 1;
}

void setWarningSound(){
    pwmSetRange(1000000/1174);
    pwmWrite(buzzer_pin, 1000000/1174/2);
}

void warningSound(){
    setWarningSound();
    turnRed();
    delay(200);
    pwmWrite(buzzer_pin,0);
    offRed();
    delay(100);
    setWarningSound();
    turnRed();
    delay(100);
    pwmWrite(buzzer_pin,0);
    offRed();
    delay(500);
}