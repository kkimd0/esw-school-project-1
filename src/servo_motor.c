#include "servo_motor.h"
#include<stdio.h>

void init_motor()
{
    pinMode ( MOTOR_PIN ,  PWM_OUTPUT ); 
    pwmSetMode ( PWM_MODE_MS ); 
	now_angle = 180;
	setAngleFast(now_angle);
}

void setServo()
{
    pwmSetClock ( 384 ); 
    pwmSetRange ( 1000 );
}

int setAngleFast(int angle)
{
    setServo();
    pwmWrite(MOTOR_PIN, 20 + angle * MOTOR_PULSE);

    return angle;
}

int setAngleSlow(int start, int end)
{
    setServo();

    if(start <= end){
        for(int i = start * MOTOR_PULSE; i <= end * MOTOR_PULSE; i++){
            pwmWrite(MOTOR_PIN, i + 20);
            delay(20);
        }
    }
    else
    {
        for(int i = start * MOTOR_PULSE; i >= end * MOTOR_PULSE; i--){
            pwmWrite(MOTOR_PIN, i + 20);
            delay(20);
        }
    }

    return end;
}

void *thread_window_up()
{
	saved_angle = now_angle;
	
	while ( servo_motor_flag && now_angle<=180 )
	{
		IR_Window_Up();
	}
	
	servo_motor_flag = 0;
	return;
}

void *thread_window_down()
{
	while ( servo_motor_flag && now_angle > 5 )
	{
		IR_Window_Down();
	}
	
	servo_motor_flag = 0;
	return;
}

void *thread_window_origin()
{
	while ( servo_motor_flag && saved_angle < now_angle )
	{
		IR_Window_Down();
	}
	
	servo_motor_flag = 0;
	return;
}

void IR_Window_Up()
{
    setServo();

    now_angle += 2;
    pwmWrite(MOTOR_PIN, 20 + now_angle * MOTOR_PULSE);
	delay(20);
	
}

void IR_Window_Down()
{
    setServo();

    now_angle -= 2;
    pwmWrite(MOTOR_PIN, 20 + now_angle * MOTOR_PULSE);
	delay(20);

}
