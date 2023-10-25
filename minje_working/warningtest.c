#include <stdio.h>
#include <wiringPi.h>
#include "warning/buzzer.h"
#include "warning/3colorLed.h"
#include "motor/servo_motor.h"


int main(){
    wiringPiSetupGpio();

    init_buzzer();
    init_3colorLed();
    init_motor();

    pinMode(20, OUTPUT);                     
    pinMode(21, INPUT);

    int distance = 0;
    int start = 0;
    int stop = 0;

    int ang = 0;

    turnGreen();

    while(1){
        digitalWrite(20, LOW);
        digitalWrite(20, HIGH);

        delay(10);
        digitalWrite(20, LOW);

        while(digitalRead(21) == 0){
            start = micros();
        }

        while(digitalRead(21) == 1){
            stop = micros();
        }

        distance = (stop - start) / 58;
        printf("Distance : %d\n", distance);

        if(distance < 20){
            warningSound();
        }else{
            turnGreen();
        }
        delay(100);
    }
}
