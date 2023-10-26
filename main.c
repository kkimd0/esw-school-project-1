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
#define SENSOR_READ_TEST	1
#define LCD_TEST 		0
/* ================================================= */

#define FRONT_DISTANCE_THRESHOLD 5
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
	wiringPiSetup();
	wiringPiSetupGpio();
	
	init_step_motor();
	init_motor();
	init_3colorLed();
	init_buzzer();
	init_sensor();
	init_LCD();
	
	carState = AUTO_OUT;
	usePrint_LCD(carState);
}

int8_t mainloop()
{
	static pthread_t pthread[5];
	static int16_t thr_id;
	static enum CarState carState_buf;
	static enum CarState carState_save;
	static int8_t camera_flag = 0;
	static int8_t air_control_dir = 1; // 0: close, 1: open
	
	read_sensor();
	/* 
	 * upDistance		: upper ultrasonic sensor
	 * frontDistance	: front ultrasonic sensor
	 * luxValue 		: illumination sensor
	 * infraredValue	: infrared sensors (remote control)
	 * joyValue 		: joystick sensor
	 */
	
	// time for log
	tnow = time(NULL);
	tm = *localtime(&tnow);
	
	// Front Warning Case
	if ( (frontDistance < FRONT_DISTANCE_THRESHOLD) )
	{
		if (carState != FRONT_WARNING && carState != SIDE_WARNING)
		{
			carState_save = carState;
		}
		
		carState = FRONT_WARNING;
	}
	// Side Warning Case
	else if ( (carState == AUTO_IN || carState == MANUAL_IN) &&
	(joyValue < LEFT_JOY_THRESHOLD || RIGHT_JOY_THRESHOLD < joyValue) )
	{
		if (carState != FRONT_WARNING && carState != SIDE_WARNING)
		{
			carState_save = carState;
		}
		carState = SIDE_WARNING;
	}
	else if( (carState == FRONT_WARNING || carState == SIDE_WARNING) &&
	((frontDistance > FRONT_DISTANCE_THRESHOLD) ||
	(LEFT_JOY_THRESHOLD < joyValue && joyValue < RIGHT_JOY_THRESHOLD)) )
	{
		carState = carState_save;
		
		usePrint_LCD(carState);
		printf("[%02d:%02d:%02d] Warning OFF\n", tm.tm_hour, tm.tm_min, tm.tm_sec, frontDistance);
		
	}
	
	// Tunnel In Case
	if ( (carState != FRONT_WARNING && carState != SIDE_WARNING) && 
	(luxValue > LUX_THRESHOLD && upDistance < UP_DISTANCE_THRESHOLD) )
	{
		isTunnelIn = 1;
		if ( !manual_mode )
		{
			carState = AUTO_IN;
		}
		else
		{
			carState = MANUAL_IN;
		}
	}
	// Tunnel Out Case
	else if ( (carState != FRONT_WARNING && carState != SIDE_WARNING) &&
	(luxValue <= LUX_THRESHOLD || upDistance >= UP_DISTANCE_THRESHOLD) )
	{
		isTunnelIn = 0;
		if ( !manual_mode )
		{
			carState = AUTO_OUT;
		}
		else
		{
			carState = MANUAL_OUT;
		}
	}
	
	
	// Front Warning Case
	if ( !buzzer_flag && carState == FRONT_WARNING )
	{
		buzzer_flag = 1;
		
		usePrint_LCD(carState);
		printf("[%02d:%02d:%02d] Front(%04d) Warning!!\n", tm.tm_hour, tm.tm_min, tm.tm_sec, frontDistance);
		
		// front buzzer thread
		thr_id = pthread_create(&pthread[0], NULL, frontWarningSound, NULL);
        if(thr_id < 0)
		{
			perror("pthread[0] create error\n");
			exit(EXIT_FAILURE);
        }
	}
	else if ( !buzzer_flag && carState == SIDE_WARNING )
	{
		buzzer_flag = 1;
		
		usePrint_LCD(carState);
		printf("[%02d:%02d:%02d] Side(%04d) Warning!!\n", tm.tm_hour, tm.tm_min, tm.tm_sec, joyValue);
		
		/* side buzzer thread */
		thr_id = pthread_create(&pthread[0], NULL, sideLaneWarningSound, NULL);
        if(thr_id < 0)
		{
			perror("pthread[0] create error\n");
			exit(EXIT_FAILURE);
        }
	}
	else if ( carState_buf != carState && carState == AUTO_IN )
	{
		carState_buf = carState;
		usePrint_LCD(carState);
		
		printf("[%02d:%02d:%02d] AutoMode Tunnel IN(Lux: %04d, Up: %04d)\n", tm.tm_hour, tm.tm_min, tm.tm_sec, luxValue, upDistance);
		
		/* window control thread */
		servo_motor_flag = 1;
		thr_id = pthread_create(&pthread[1], NULL, thread_window_up, NULL);
		if(thr_id < 0)
		{
			perror("pthread[1] create error\n");
			exit(EXIT_FAILURE);
		}
		
		/* air control thread */
		step_motor_flag = 1;
		air_control_dir = 0;
		thr_id = pthread_create(&pthread[2], NULL, close_rotation, NULL);
		if(thr_id < 0)
		{
			perror("pthread[2] create error\n");
			exit(EXIT_FAILURE);
		}
		
	}
	else if ( carState_buf != carState && carState == MANUAL_IN )
	{
		carState_buf = carState;
		usePrint_LCD(carState);
		
		printf("[%02d:%02d:%02d] ManualMode Tunnel IN(Lux: %04d, Up: %04d)\n", tm.tm_hour, tm.tm_min, tm.tm_sec, luxValue, upDistance);
	}
	else if ( carState_buf != carState && carState == AUTO_OUT )
	{
		carState_buf = carState;
		usePrint_LCD(carState);
		
		printf("[%02d:%02d:%02d] AutoMode Tunnel OUT(Lux: %04d, Up: %04d)\n", tm.tm_hour, tm.tm_min, tm.tm_sec, luxValue, upDistance);
		
		/* window control thread */
		servo_motor_flag = 1;
		thr_id = pthread_create(&pthread[1], NULL, thread_window_origin, NULL);
		if(thr_id < 0)
		{
			perror("pthread[1] create error\n");
			exit(EXIT_FAILURE);
		}
		
		/* air control thread */
		step_motor_flag = 1;
		air_control_dir = 1;
		thr_id = pthread_create(&pthread[2], NULL, open_rotation, NULL);
		if(thr_id < 0)
		{
			perror("pthread[2] create error\n");
			exit(EXIT_FAILURE);
		}
		
	}
	else if ( carState_buf != carState && carState == MANUAL_OUT)
	{
		carState_buf = carState;
		usePrint_LCD(carState);
		
		printf("[%02d:%02d:%02d] ManualMode Tunnel OUT(Lux: %04d, Up: %04d)\n", tm.tm_hour, tm.tm_min, tm.tm_sec, luxValue, upDistance);
	}
	
	/* Camera Deactivate */
	if ( camera_flag && !isTunnelIn )
	{
		camera_flag = 0;
		system("camera/kill_stream.sh");
	}
	/* Camera Activate */
	else if ( !camera_flag && isTunnelIn )
	{
		camera_flag = 1;
		system("python3 camera/stream.py &");
	}
	
	/* Remote control
	 * 		window up
	 *		window down
	 * 		air control
	 */
	
	/* window up */
	if ( !infrared_flag && infraredValue == 10 )
	{
		infrared_flag = 1;
		
		if ( servo_motor_flag )
		{
			servo_motor_flag = 0;
			printf("[%02d:%02d:%02d] window up stop\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		}
		else
		{
			servo_motor_flag = 1;
			
			thr_id = pthread_create(&pthread[1], NULL, thread_window_up, NULL);
			if(thr_id < 0)
			{
				perror("pthread[1] create error\n");
				exit(EXIT_FAILURE);
			}
			printf("[%02d:%02d:%02d] window up\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		}
		
		
		thr_id = pthread_create(&pthread[4], NULL, infrared_contorl, NULL);
		if(thr_id < 0)
		{
			perror("pthread[4] create error\n");
			exit(EXIT_FAILURE);
		}
		
	}
	/* window down */
	else if ( !infrared_flag && infraredValue == 20 )
	{
		infrared_flag = 1;
		
		if ( servo_motor_flag )
		{
			servo_motor_flag = 0;
			printf("[%02d:%02d:%02d] window down stop\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		}
		else
		{
			servo_motor_flag = 1;
			
			thr_id = pthread_create(&pthread[1], NULL, thread_window_down, NULL);
			if(thr_id < 0)
			{
				perror("pthread[1] create error\n");
				exit(EXIT_FAILURE);
			}
			printf("[%02d:%02d:%02d] window down\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		}
		
		
		thr_id = pthread_create(&pthread[4], NULL, infrared_contorl, NULL);
		if(thr_id < 0)
		{
			perror("pthread[4] create error\n");
			exit(EXIT_FAILURE);
		}
	}
	/* air control */
	else if ( !infrared_flag && infraredValue == 30 )
	{
		infrared_flag = 1;
		
		if ( step_motor_flag )
		{
			step_motor_flag = 0;
			usleep( 100000 );
		}
		
		step_motor_flag = 1;
		if ( !air_control_dir )
		{
			air_control_dir = 1;
			thr_id = pthread_create(&pthread[2], NULL, open_rotation, NULL);
			if(thr_id < 0)
			{
				perror("pthread[2] create error\n");
				exit(EXIT_FAILURE);
			}
			printf("[%02d:%02d:%02d] air control open\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		}
		else
		{
			air_control_dir = 0;
			thr_id = pthread_create(&pthread[2], NULL, close_rotation, NULL);
			if(thr_id < 0)
			{
				perror("pthread[2] create error\n");
				exit(EXIT_FAILURE);
			}
			printf("[%02d:%02d:%02d] air control close\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		}
		
		thr_id = pthread_create(&pthread[4], NULL, infrared_contorl, NULL);
		if(thr_id < 0)
		{
			perror("pthread[4] create error\n");
			exit(EXIT_FAILURE);
		}
		
	}
	
	return 0;
}

void switch_toggle_callback()
{
	manual_mode = !manual_mode;
}

int main()
{
	init();
	printf("init complete\n");
	if ( MODULE_TEST )
	{
		module_test();
	}
	
	
	if( wiringPiISR(GPIO_MANUAL, INT_EDGE_RISING, &switch_toggle_callback) < 0 )
	{
		printf("%s\n", "Interrupt setup Fail");
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
		while (1)
		{
			read_sensor();
			printf("UP: %d\n", upDistance);
			printf("FRONT: %d\n", frontDistance);
			printf("LUX: %d\n", luxValue);
			printf("INFRARED: %d\n", infraredValue);
			printf("JOY_Z: %d\n", joyValue);
			usleep(1000);
		}
		printf("sensor reading test complete\n");
		
		sleep(1);
	}
	
	if ( LCD_TEST )
	{
		printf("lcd test start\n");
		while (1)
		{
			carState = AUTO_IN;
			usePrint_LCD(carState);
			printf("AUTO_IN\n");
			sleep(1);
			
			carState = MANUAL_IN;
			usePrint_LCD(carState);
			printf("MANUAL_IN\n");
			sleep(1);
			
			carState = MANUAL_OUT;
			usePrint_LCD(carState);
			printf("MANUAL_OUT\n");
			sleep(1);
			
			carState = AUTO_OUT;
			usePrint_LCD(carState);
			printf("AUTO_OUT\n");
			sleep(1);
		}
		printf("lcd test complete\n");
		
		sleep(1);
	}

	printf("All test complete\n");
}
