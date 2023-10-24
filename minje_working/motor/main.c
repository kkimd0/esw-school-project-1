#include <stdio.h>
#include <wiringPi.h>
#include "myMotor.h"

int main(){
    if (wiringPiSetup() == -1) {
        return 1;
    }

    wiringPiSetupGpio();
    init_motor();

    while  ( 1 )  { 

        angle(0, 180);
        delay(200);
        angle(180,0);
        delay(200);
    }
}