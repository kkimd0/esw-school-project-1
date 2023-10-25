#include "servo_motor.h"
#include<stdio.h>

void init_motor()
{
    pinMode ( MOTOR_PIN ,  PWM_OUTPUT ); 
    pwmSetMode ( PWM_MODE_MS ); 
}

void setServo()
{
    pwmSetClock ( 384 ); 
    pwmSetRange ( 1000 );
}

void setAngleFast(int angle)
{
    setServo();
    pwmWrite(MOTOR_PIN, 20 + angle * MOTOR_PULSE);
}

void setAngleSlow(int start, int end)
{
    setServo();

    if(start <= end){
        for(int i = start * MOTOR_PULSE; i <= end * MOTOR_PULSE; i++){
            pwmWrite(MOTOR_PIN, i + 20);
            delay(20);
        }
    }
    else
    {
        for(int i = start * MOTOR_PULSE; i >= end * MOTOR_PULSE; i--){
            pwmWrite(MOTOR_PIN, i + 20);
            delay(20);
        }
    }
}

void IR_Window_Up(int* currangle)
{
    setServo();
    if(currangle >= 180)
    {
        return;
    }
    currangle = currangle + 2;
    pwmWrite(MOTOR_PIN, 20 + currangle * MOTOR_PULSE);
}

void IR_Window_Down(int* currangle)
{
    setServo();
    if(currangle <= 0)
    {
        return;
    }
    currangle = currangle - 2;
    pwmWrite(MOTOR_PIN, 20 + currangle * MOTOR_PULSE);
}
