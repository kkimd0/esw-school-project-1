#include "servo_motor.h"
#include <stdio.h>

static uint16_t now_value;
static uint16_t saved_value;

void init_servo_motor()
{
	pinMode( MOTOR_PIN, OUTPUT );
	
	now_value = CLOSEWINDOW;
	saved_value = CLOSEWINDOW;
	for(int i=0; i<20; i++)
	{
		digitalWrite(MOTOR_PIN, 1);
		usleep(CLOSEWINDOW);
		digitalWrite(MOTOR_PIN, 0);
		usleep(PULSE - CLOSEWINDOW);
	}
	
	return;
}

void setAngle(uint16_t value)
{
	for(int i=0; i<2; i++)
	{
		digitalWrite(MOTOR_PIN, 1);
		usleep(value);
		digitalWrite(MOTOR_PIN, 0);
		usleep(PULSE - value);
	}
}

void *thread_window_up()
{
	saved_value = now_value;
	
	while ( (servo_motor_flag) && (now_value < CLOSEWINDOW) )
	{
		IR_Window_Up();
	}
	
	servo_motor_flag = 0;
	
	return 0;
}

void *thread_window_down()
{
	while ( (servo_motor_flag) && (now_value > OPENWINDOW) )
	{
		IR_Window_Down();
	}
	
	servo_motor_flag = 0;
	
	return 0;
}

void *thread_window_origin()
{
	while ( (servo_motor_flag) && (saved_value < now_value) )
	{
		IR_Window_Down();
	}
	
	servo_motor_flag = 0;
	
	return 0;
}

void IR_Window_Up()
{
	/* from 500 to 2500 */
    now_value += 80;
    setAngle(now_value);
	usleep(SET_DELAY);
}

void IR_Window_Down()
{
	/* from 2500 to 500 */
    now_value -= 80;
    setAngle(now_value);
	usleep(SET_DELAY);
}
