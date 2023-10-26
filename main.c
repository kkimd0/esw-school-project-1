/*
 * main program
 * 1. execute init() function.
 * 2. if MODULE_TEST is 1, it'll start module test.
 * 3. if MAINLOOP is 1, main program loop will start.
 ** 4. now, error code and flag is making.
 * write by siyun
 */

#include "step_motor/step_motor.h"
#include "minje_working/motor/servo_motor.h"
#include "minje_working/warning/3colorLed.h"
#include "minje_working/warning/buzzer.h"
#include "sungyj_working/LCD.h"
#include "sensor.h"

#define MAINLOOP		1
#define MODULE_TEST		0

/* == if MODULE_TEST is 0, disable the test below == */
#define STEP_MOTOR_TEST		0
#define SERVO_MOTOR_TEST	0
#define LED_TEST		0
#define BUZZER_TEST		0
#define SENSOR_READ_TEST	0
/* ================================================= */

#define FRONT_DISTANCE_THRESHOLD 100
#define UP_DISTANCE_THRESHOLD 100
#define LEFT_JOY_THRESHOLD 250
#define RIGHT_JOY_THRESHOLD 750
#define LUX_THRESHOLD 600
#define OPEN_WINDOW_VALUE 180
#define CLOSE_WINDOW_VALUE 0

static time_t tnow;
static struct tm tm;
static int8_t manual_mode;
static int8_t isTunnelIn;
	
void module_test();
void init()
{
	wiringPiSetupGpio();
	init_step_motor();
	init_motor();
	init_3colorLed();
	init_buzzer();
	init_sensor();
}

int8_t mainloop()
{
	static pthread_t pthread[3];
	static int16_t thr_id;
	// read_sensor();
	/* 
	 * upDistance		: upper ultrasonic sensor
	 * frontDistance	: front ultrasonic sensor
	 * luxValue 		: illumination sensor
	 * infraedValue		: infrared sensors (remote control)
	 * joyValue 		: joystick sensor
	 */
	
	// Front Warning Case
	if ( !buzzer_flag && (frontDistance < FRONT_DISTANCE_THRESHOLD) )
	{
		buzzer_flag = 1;
		tnow = time(NULL);
		tm = *localtime(&tnow);
		usePrint_LCD(0);
		printf("[%02d:%02d:%02d] Front(%04d) Warning!!\n", tm.tm_hour, tm.tm_min, tm.tm_sec, frontDistance);
		
		// front buzzer thread
		thr_id = pthread_create(&pthread[0], NULL, frontWarningSound, NULL);
        if(thr_id < 0)
		{
			perror("pthread[0] create error\n");
			exit(EXIT_FAILURE);
        }
	}
	
	// Side Warning Case
	if ( !buzzer_flag && (carState == AUTO_IN || carState == MANUAL_IN) &&
	(LEFT_JOY_THRESHOLD <= joyValue || joyValue <= RIGHT_JOY_THRESHOLD) )
	{
		buzzer_flag = 1;
		tnow = time(NULL);
		tm = *localtime(&tnow);
		usePrint_LCD(0);
		printf("[%02d:%02d:%02d] Side(%04d) Warning!!\n", tm.tm_hour, tm.tm_min, tm.tm_sec, frontDistance);
		
		// side buzzer thread
		thr_id = pthread_create(&pthread[0], NULL, sideLaneWarningSound, NULL);
        if(thr_id < 0)
		{
			perror("pthread[0] create error\n");
			exit(EXIT_FAILURE);
        }
	}
	
	// Tunnel In Case
	if ( !isTunnelIn && (luxValue > LUX_THRESHOLD && upDistance < UP_DISTANCE_THRESHOLD) )
	{
		isTunnelIn = 1;
		if ( !manual_mode )
		{
			carState = AUTO_IN;
			tnow = time(NULL);
			tm = *localtime(&tnow);
			
			usePrint_LCD(carState);
			printf("[%02d:%02d:%02d] AutoMode Tunnel IN(Lux: %04d, Up: %04d)\n", tm.tm_hour, tm.tm_min, tm.tm_sec, luxValue, upDistance);
			
			/* 창문 컨트롤 스레드 */
			/* 공조 컨트롤 스레드 */
		}
		else
		{
			carState = MANUAL_IN;
			tnow = time(NULL);
			tm = *localtime(&tnow);
			
			usePrint_LCD(carState);
			printf("[%02d:%02d:%02d] ManualMode Tunnel IN(Lux: %04d, Up: %04d)\n", tm.tm_hour, tm.tm_min, tm.tm_sec, luxValue, upDistance);
		}
		
	}
	// Tunnel Out Case
	else if ( isTunnelIn && (luxValue <= LUX_THRESHOLD || upDistance >= UP_DISTANCE_THRESHOLD) )
	{
		isTunnelIn = 0;
		if ( !manual_mode )
		{
			carState = AUTO_OUT;
			tnow = time(NULL);
			tm = *localtime(&tnow);
			
			usePrint_LCD(carState);
			printf("[%02d:%02d:%02d] AutoMode Tunnel OUT(Lux: %04d, Up: %04d)\n", tm.tm_hour, tm.tm_min, tm.tm_sec, luxValue, upDistance);
			
			thr_id = pthread_create(&pthread[1], NULL, sideLaneWarningSound, NULL);
			if(thr_id < 0)
			{
				perror("pthread[1] create error\n");
				exit(EXIT_FAILURE);
			}
			
			/* 창문 컨트롤 스레드 */
			/* 공조 컨트롤 스레드 */
		}
		else
		{
			carState = MANUAL_OUT;
			tnow = time(NULL);
			tm = *localtime(&tnow);
			
			usePrint_LCD(carState);
			printf("[%02d:%02d:%02d] ManualMode Tunnel OUT(Lux: %04d, Up: %04d)\n", tm.tm_hour, tm.tm_min, tm.tm_sec, luxValue, upDistance);
		}
		
	}
	
	// 리모컨 컨트롤
	// 창문 올림
	// 창문 내림
	// 공조 컨트롤
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
	while ( MAINLOOP )
	{
		er = mainloop();
	}
	return 0;
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
		for (uint8_t i=0; i<100; i++)
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
