#include "step_motor/step_motor.h"
#include "minje_working/motor/servo_motor.h"
#include "minje_working/warning/3colorLed.h"
#include "minje_working/warning/buzzer.h"
#include "sensor.h"

void init()
{
	wiringPiSetupGpio();
	init_step_motor();
    init_motor();
	init_3colorLed();
    init_buzzer();
}

int main()
{
	init();
	printf("init complete\n");
	sleep(1);
	
	printf("step_motor one_cycle_rotation start\n");
	one_cycle_rotation();
	motor_reset();
	printf("step_motor one_cycle_rotation complete\n");

	sleep(3);
	
	printf("step_motor one_cycle_reverse_rotation start\n");
	one_cycle_reverse_rotation();
	motor_reset();
	printf("step_motor one_cycle_reverse_rotation complete\n");
	
	sleep(1);
	printf("servo_motor test start\n");
	angle(0, 180);
	sleep(1);
	angle(180,0);
	sleep(1);
	printf("servo_motor test complete\n");
	
	sleep(1);
	printf("3LED turn green\n");
    	turnGreen();
	printf("3LED turn green complete\n");
    	sleep(3);

	printf("test warningSound start\n");
    	for(int i=0; i<5; i++)
	{
        	warningSound();
    	}
	printf("test warningSound complete\n");

	printf("All test complete\n");
	return 0;
}

