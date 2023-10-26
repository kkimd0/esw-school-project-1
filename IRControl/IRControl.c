#include <stdio.h>
#include <wiringPi.h>
#include "servo_motor.h"
#include <stdint.h>

uint8_t prevstate;

int main()
{
	wiringPiSetupGpio();
	init_motor();
	angle(0, 90);


	return 0;
}
