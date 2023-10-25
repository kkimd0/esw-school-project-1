#include <wiringPi.h>
#include "servo_motor.h"

int main(){

    wiringPiSetupGpio();
    init_motor();

    setAngleFast(180);

    while(1){
        // setAngleFast(180);
        // delay(500);
        // setAngleFast(0);
        // delay(500);

        setAngleSlow(180, 0);
        setAngleSlow(0, 180);
    }
}