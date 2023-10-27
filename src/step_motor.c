/*
 * step_motor.c
 * write by siyun
 */

#include "step_motor.h"
void motor_step(uint8_t step);

void init_step_motor()
{
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	
	motorDelay = 800;	// motor_delay set default value
	motor_step(0); 		// motor reset
}

void motor_reset()
{
	motor_step(0);
}

void one_step_rotation()
{
	for (uint8_t i=1; i<=8; i++)
	{
		motor_step(i);
	}
}

void one_cycle_rotation()
{
	for (uint16_t i=1; i<=512; i++)
	{
		one_step_rotation();
	}
}

void one_step_reverse_rotation()
{
	for (uint8_t i=8; i>0; i--)
	{
		motor_step(i);
	}
}

void one_cycle_reverse_rotation()
{
	for (uint16_t i=1; i<=512; i++)
	{
		one_step_reverse_rotation();
	}
}

void *close_rotation()
{
	while ( (step_motor_flag) && (0 < cnt) )
	{
		one_step_reverse_rotation();
		cnt--;
	}
	
	motor_step(0); 		// motor reset
	step_motor_flag = 0;
	return;
}

void *open_rotation()
{
	while ( (step_motor_flag) && (255 > cnt) )
	{
		one_step_rotation();
		cnt++;
	}
	
	motor_step(0); 		// motor reset
	step_motor_flag = 0;
	return;
}

void set_motor_speed(uint32_t motor_delay)
{
	motorDelay = motor_delay;
}

void motor_step(uint8_t step)
{
	switch(step)
	{
		case 1:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, HIGH);
			usleep(motorDelay);
			break;
			
		case 2:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, HIGH);
			digitalWrite(IN4, HIGH);
			usleep(motorDelay);
			break;
			
		case 3:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, HIGH);
			digitalWrite(IN4, LOW);
			usleep(motorDelay);
			break;
			
		case 4:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, HIGH);
			digitalWrite(IN3, HIGH);
			digitalWrite(IN4, LOW);
			usleep(motorDelay);
			break;
		
		case 5:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, HIGH);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, LOW);
			usleep(motorDelay);
			break;
			
		case 6:
			digitalWrite(IN1, HIGH);
			digitalWrite(IN2, HIGH);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, LOW);
			usleep(motorDelay);
			break;
		
		case 7:
			digitalWrite(IN1, HIGH);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, LOW);
			usleep(motorDelay);
			break;
			
		case 8:
			digitalWrite(IN1, HIGH);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, HIGH);
			usleep(motorDelay);
			break;
			
		default:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, LOW);
			usleep(motorDelay);
			break;
	}
}
