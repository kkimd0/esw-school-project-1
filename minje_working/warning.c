#include <stdio.h>
#include <wiringPi.h>
#include "3colorLed.h"
#include "buzzer.h"

void init();

int main(void) 
{
    if (wiringPiSetup() == -1) {
        return 1;
    }

    wiringPiSetupGpio();

    init_3colorLed();
    init_buzzer();

    turnGreen();

    delay(5000);

    for(int i=0;i<5;i++){
        warningSound();
    }
    
}
