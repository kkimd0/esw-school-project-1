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

int upDistance = 0;
int frontDistance = 0;
int luxValue = 0;
int infraedValue = 0;
int joyValue = 0;

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

  // delay(7000);
}
 
void loop() {

  if(serialDataAvail(fd)) {
    char c = serialGetchar(fd);
    int flag = strcmp(&c, &testletter);

    if(flag < 0) {
    	buffer[index_buf] = c;
	index_buf = index_buf + 1;
    	if(index_buf >= sizeof(buffer)) {
		index_buf--;
 	}
    }

    else {
    	buffer[index_buf] = '\0';

    	char sensor[16];
    	int value;

    	sscanf(buffer, "%[^:]:%d", sensor, &value);
 
	// read signal
    	if(strcmp(sensor, "UP") == 0) {
            upDistance = value; 
    	} 
    	else if(strcmp(sensor, "FRONT") == 0) {
            frontDistance = value; 
    	} 
    	else if(strcmp(sensor, "LUX") == 0) {
            luxValue = value; 
    	}
	else if(strcmp(sensor, "INFRAED") == 0) {
	    infraedValue = value;
	}
	else if(strcmp(sensor, "JOY") == 0) {
	    joyValue = value;
	}

    	printf("UP: %d\n", upDistance);
    	printf("FRONT: %d\n", frontDistance);
    	printf("LUX: %d\n", luxValue);
	printf("INFRAED: %d\n", infraedValue);
	printf("JOY_Z: %d\n", joyValue);

        index_buf = 0;
     	memset(buffer, 0, sizeof(buffer)); // buffer
    }
  }
}
 
// main function for normal c++ programs on Raspberry
int main(){
  setup();
  while(1) loop();
  return 0;
}
 
#endif //#ifdef RaspberryPi
