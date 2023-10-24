#include "buzzer.h"

void init_buzzer()
{
    
    pinMode(BUZZER_PIN, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
}

void setWarningSound()
{
    pwmSetClock(19);
    pwmSetRange(MICROSECOND/NOTE_D6);
    pwmWrite(BUZZER_PIN, MICROSECOND/NOTE_D6 * DUTY_CYCLE);
}

void warningSound()
{
    setWarningSound();
    
    turnRed();
    delay(200);
    pwmWrite(BUZZER_PIN,0);
    offRed();
    delay(100);
    setWarningSound();
    turnRed();
    delay(100);
    pwmWrite(BUZZER_PIN,0);
    offRed();
    delay(500);
}