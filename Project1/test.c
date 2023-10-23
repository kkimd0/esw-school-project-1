// just that the Arduino IDE doesnt compile these files.
#ifdef RaspberryPi 
 
//include system librarys
#include <stdio.h> //for printf
#include <stdint.h> //uint8_t definitions
#include <stdlib.h> //for exit(int);
#include <string.h> //for errno
#include <errno.h> //error output
 
//wiring Pi
#include <wiringPi.h>
#include <wiringSerial.h>
 
// Find Serial device on Raspberry with ~ls /dev/tty*
// ARDUINO_UNO "/dev/ttyACM0"
// FTDI_PROGRAMMER "/dev/ttyUSB0"
// HARDWARE_UART "/dev/ttyAMA0"
char device[]= "/dev/ttyACM0";
// filedescriptor
int fd;
unsigned long baud = 9600;
 
//prototypes
int main(void);
void loop(void);
void setup(void);
 
void setup(){

  wiringPiSetupGpio();
 
  // printf("%s \n", "Raspberry Startup!");
  // fflush(stdout);
 
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
 
void loop(){
 
  // read signal
  if(serialDataAvail(fd)) {
    char data = serialGetchar(fd);
    printf("%c", data);
  }
}
 
// main function for normal c++ programs on Raspberry
int main(){
  setup();
  while(1) loop();
  return 0;
}
 
#endif //#ifdef RaspberryPi
