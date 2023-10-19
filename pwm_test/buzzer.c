#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h> 

#define BUZZER 23

int main()
{
    if(wiringPiSetup()==-1)
        return 1;
    pinMode(BUZZER, PWM_OUTPUT);

    softPwmCreate(BUZZER, 0, 500);

    while(1)
    {   
	softPwmWrite(BUZZER, 10);
    }

    pinMode(BUZZER, INPUT);
    digitalWrite(BUZZER, LOW);   

    return 0;
}
