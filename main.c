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

void module_test()
{
	uint8_t cnt = 0;
	if ( 1 )
	{
		printf("step_motor test start\n");
		printf("step_motor one_cycle_rotation start\n");
		one_cycle_rotation();
		motor_reset();
		printf("step_motor one_cycle_rotation complete\n");

		sleep(1);
		
		printf("step_motor one_cycle_reverse_rotation start\n");
		one_cycle_reverse_rotation();
		motor_reset();
		printf("step_motor one_cycle_reverse_rotation complete\n");
		printf("step_motor test complete\n");
		
		sleep(1);
		cnt++;
	}
	
	if ( 1 )
	{
		printf("servo_motor test start\n");
		angle(0, 180);
		delay(200);
		angle(180,0);
		delay(200);
		printf("servo_motor test complete\n");
		
		sleep(1);
		cnt++;
	}
	
	if ( 1 )
	{
		printf("3LED turn green\n");
    	turnGreen();
		printf("3LED turn green complete\n");
		
    	sleep(1);
		cnt++;
	}
	
	if ( 1 )
	{
		printf("buzzer test start\n");
		for(int i=0; i<5; i++)
		{
			warningSound();
		}
		printf("buzzer test complete\n");
		
		sleep(1);
		cnt++;
	}
	
	if ( !cnt )
	{
		printf("no module test\n");
	}
	else
	{
		printf("All test complete\n");
	}
}

int main()
{
	init();
	printf("init complete\n");
	module_test();
	
	return 0;
}

