#include <wiringPi.h>
#include "servo_motor.h"

int main(){

    wiringPiSetupGpio();
    init_motor();

    setAngleFast(0);

    while(1){
        // setAngleFast(10);
        // delay(500);
        // setAngleFast(0);
        // delay(500);

        setAngleSlow(180, 0);
        setAngleSlow(0, 180);
    }
}