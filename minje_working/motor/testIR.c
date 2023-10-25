#include <wiringPi.h>
#include <stdio.h>
#include "servo_motor.h"

int main(){

    wiringPiSetupGpio();
    init_motor();
    int now = 0;
    setAngleFast(now);

    while(1)
    {
        int IRinput;
        scanf("%d", &IRinput);
        if(IRinput == 10)
        {
            IR_Window_Up(now);
        }
        else if(IRinput == 20)
        {
            IR_Window_Down(now);
        }
    }
}
