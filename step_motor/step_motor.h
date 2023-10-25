/*
 * step_motor.h
 * step_motor_control
 * write by siyun
 */
#ifndef __STEP_MOTOR_H__
#define __STEP_MOTOR_H__

#include <unistd.h>
#include <wiringPi.h>
#include <stdint.h>

#define IN1 23
#define IN2 24
#define IN3 25
#define IN4 8
static uint32_t motorDelay;

// motor setting function
void init_step_motor();

// motor reset
void motor_reset();

// (0.703125) angle forward rotation
// 512 active for 1 cycle
void one_step_rotation();

// 1 cycle forward rotation
void one_cycle_rotation();

// (0.703125) angle backward rotation
// 512 active for 1 cycle
void one_step_reverse_rotation();

// 1 cycle backward rotation
void one_cycle_reverse_rotation();

// set step delay
// higher motor delay, slower
// max speed delay value: 700
void set_motor_speed(uint32_t motor_delay);

#endif
