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
extern uint32_t fd;
extern uint32_t upDistance;
extern uint32_t frontDistance;
extern uint32_t luxValue;
extern uint32_t infraedValue;
extern uint32_t joyValue;

// init sensor setting
void init_sensor();

// read all sensor value
void read_sensor();

#endif
