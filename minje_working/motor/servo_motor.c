#include "servo_motor.h"
#include<stdio.h>

void init_motor()
{
    pinMode ( MOTOR_PIN ,  PWM_OUTPUT ); 
    pwmSetMode ( PWM_MODE_MS ); 
}

void setServo(){
    pwmSetClock ( 400 ); 
    pwmSetRange ( 1024 );
    
}

void angle(int status, int value)
{
    setServo();

    if(status < value)
    {
        for(int i=status;i<=value;i++)
        {
            printf("%d\n", i);
            pwmWrite (MOTOR_PIN,  i); 
            delay(10);
        }
    }
    else
    {
        for(int i=status;i>=value;i--)
        {
            pwmWrite (MOTOR_PIN,  i); 
            delay(10);
        }
    }

}