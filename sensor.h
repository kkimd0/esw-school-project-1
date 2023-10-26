/*
 * Sensor.h
 * Public header files for receiving and using sensor value
 * write by siyun
 */

#ifndef __SENSOR_H__
#define __SENSOR_H__
//include system librarys
#include <stdio.h> //for printf
#include <stdint.h> //uint8_t definitions
#include <stdlib.h> //for exit(int);
#include <string.h> //for errno
#include <errno.h> //error output
#include <pthread.h>
#include <time.h>
 
//wiring Pi
#include <wiringPi.h>
#include <wiringSerial.h>

#define SERIALBAUD 9600
#define DEVICE "/dev/ttyACM0"

// Find Serial device on Raspberry with ~ls /dev/tty*
// ARDUINO_UNO "/dev/ttyACM0"
// FTDI_PROGRAMMER "/dev/ttyUSB0"
// HARDWARE_UART "/dev/ttyAMA0"
// filedescriptor

// common value
extern uint32_t upDistance;
extern uint32_t frontDistance;
extern uint32_t luxValue;
extern uint32_t infraedValue;
extern uint32_t joyValue;
extern enum CarState carState;

// common flag
extern int8_t servo_motor_flag;
extern int8_t step_motor_flag;
extern int8_t buzzer_flag;

// Car State Enum
enum CarState 
{
	WARNING,
	AUTO_IN,
	MANUAL_IN,
	MANUAL_OUT,
	AUTO_OUT
};

// init sensor setting
void init_sensor();

// read all sensor value
void read_sensor();

#endif
