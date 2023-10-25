/*
 * Sensor.h
 * Public header files for receiving and using sensor value
 * write by siyun
 */
#pragma once
//include system librarys
#include <stdio.h> //for printf
#include <stdint.h> //uint8_t definitions
#include <stdlib.h> //for exit(int);
#include <string.h> //for errno
#include <errno.h> //error output
 
//wiring Pi
#include <wiringPi.h>
#include <wiringSerial.h>

#define serialBaud 9600

// Find Serial device on Raspberry with ~ls /dev/tty*
// ARDUINO_UNO "/dev/ttyACM0"
// FTDI_PROGRAMMER "/dev/ttyUSB0"
// HARDWARE_UART "/dev/ttyAMA0"
int8_t device[]= "/dev/ttyACM0";
// filedescriptor
uint32_t fd;
unsigned long baud = 9600;
uint32_t upDistance = 0;
uint32_t frontDistance = 0;
uint32_t luxValue = 0;
uint32_t infraedValue = 0;
uint32_t joyValue = 0;


char buffer[256];
int index_buf = 0;
char testletter = 'q';


void setup(){

  wiringPiSetupGpio();
 
  //get filedescriptor
  if ((fd = serialOpen (device, baud)) < 0){
    printf ("Unable to open serial device\n");
    exit(1); //error
  }
 
  //setup GPIO in wiringPi mode
  if (wiringPiSetup () == -1){
    printf ("Unable to start wiringPi\n");
    exit(1); //error
  }
}
 
