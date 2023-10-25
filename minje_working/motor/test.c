#include <wiringPi.h>
#include "servo_motor.h"

int main(){



    wiringPiSetupGpio();
    init_motor();
    setServo();

    while(1){
        // pwmWrite(MOTOR_PIN, 180 );
        // delay(1000);

        // pwmWrite(MOTOR_PIN, 0 );
        // delay(1000);

        angle(20, 30);
        angle(30, 20);

    }
}