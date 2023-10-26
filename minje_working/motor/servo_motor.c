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

int setAngleFast(int angle)
{
    setServo();
    pwmWrite(MOTOR_PIN, 20 + angle * MOTOR_PULSE);

    return angle;
}

int setAngleSlow(int start, int end)
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

    return end;
}

int IR_Window_Up(int currentAngle)
{
    setServo();

    int nextAngle = currentAngle + 2;
    pwmWrite(MOTOR_PIN, 20 + nextAngle * MOTOR_PULSE);

    return nextAngle;
}

void IR_Window_Down(int currentAngle)
{
    setServo();

    int nextAngle = currentAngle - 2;
    pwmWrite(MOTOR_PIN, 20 + nextAngle * MOTOR_PULSE);

    return nextAngle;
}
