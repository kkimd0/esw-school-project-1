#include "step_motor/step_motor.h"
#include "minje_working/motor/servo_motor.h"
#include "minje_working/warning/3colorLed.h"
#include "minje_working/warning/buzzer.h"
#include "sensor.h"

#define MODULE_TEST		1
/* == if MODULE_TEST is 0, disable the test below == */
#define STEP_MOTOR_TEST		0
#define SERVO_MOTOR_TEST	0
#define LED_TEST		0
#define BUZZER_TEST		0
#define SENSOR_READ_TEST	1
/* ================================================= */

void init()
{
	wiringPiSetupGpio();
	init_step_motor();
	init_motor();
	init_3colorLed();
	init_buzzer();
	init_sensor();
}

void module_test()
{
	if ( STEP_MOTOR_TEST )
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
	}
	
	if ( SERVO_MOTOR_TEST )
	{
		printf("servo_motor test start\n");
		angle(0, 180);
		delay(200);
		angle(180,0);
		delay(200);
		printf("servo_motor test complete\n");
		
		sleep(1);
	}
	
	if ( LED_TEST )
	{
		printf("3LED turn green\n");
    		turnGreen();
		printf("3LED turn green complete\n");
		
    	sleep(1);
	}
	
	if ( BUZZER_TEST )
	{
		printf("buzzer test start\n");
		for(int8_t i=0; i<5; i++)
		{
			frontWarningSound();
		}
		printf("buzzer test complete\n");
		
		sleep(1);
	}
	
	if ( SENSOR_READ_TEST )
	{
		printf("sensor reading test start\n");
		while(1)
		{
			read_sensor();
			printf("UP: %d\n", upDistance);
			printf("FRONT: %d\n", frontDistance);
			printf("LUX: %d\n", luxValue);
			printf("INFRAED: %d\n", infraedValue);
			printf("JOY_Z: %d\n", joyValue);
		}
		printf("sensor reading test complete\n");
		
		sleep(1);
	}

	printf("All test complete\n");
}

int8_t mainloop()
{
	return 0;
}

int main()
{
	init();
	printf("init complete\n");
	if ( MODULE_TEST )
	{
		module_test();
	}

	int8_t er;
	while ( 0 )
	{
		er = mainloop();
	}
	return 0;
}

