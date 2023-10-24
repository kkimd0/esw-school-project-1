#include "step_motor/step_motor.h"
#include "sensor.h"

int main()
{
	step_motor_set();
	sleep(1);
	
	one_cycle_rotation();
	motor_reset();
	
	sleep(3);
	
	one_cycle_reverse_rotation();
	motor_reset();
	
	return 0;
}

