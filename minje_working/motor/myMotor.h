#pragma once

#include <wiringPi.h>

#define motor_pin 12

void init_motor(){
    pinMode ( motor_pin ,  PWM_OUTPUT ); 
    pwmSetMode ( PWM_MODE_MS ); 
    pwmSetClock ( 400 ); 
    pwmSetRange ( 1024 );
}

void angle(int status, int value){

    if(status < value)
    {
        for(int i=status;i<=value;i++)
        {
            pwmWrite (motor_pin,  i); 
            delay(10);
        }
    }
    else
    {
        for(int i=status;i>=value;i--)
        {
            pwmWrite (motor_pin,  i); 
            delay(10);
        }
    }

}

