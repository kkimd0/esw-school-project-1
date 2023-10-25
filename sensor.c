#include "sensor.h"

static uint32_t fd;
uint32_t upDistance = 0;
uint32_t frontDistance = 0;
uint32_t luxValue = 0;
uint32_t infraedValue = 0;
uint32_t joyValue = 0;

void init_sensor()
{
	//get filedescriptor
	if ((fd = serialOpen (DEVICE, SERIALBAUD)) < 0)
	{
		printf ("Unable to open serial device\n");
		exit(1); //error
	}

	//setup GPIO in wiringPi mode
	if (wiringPiSetup () == -1)
	{
		printf ("Unable to start wiringPi\n");
		exit(1); //error
	}
}
 
void read_sensor()
{
	static int8_t buffer[256];
	static int8_t index_buf = 0;
	static int8_t testletter = 'q';
	
	if(serialDataAvail(fd)) 
	{
		int8_t c = serialGetchar(fd);
		int16_t flag = strcmp(&c, &testletter);

		if(flag < 0) 
		{
			buffer[index_buf] = c;
			index_buf = index_buf + 1;
			if(index_buf >= sizeof(buffer)) 
			{
				index_buf--;
			}
		}
		else 
		{
			buffer[index_buf] = '\0';

			int8_t sensor[16];
			int32_t value;

			sscanf(buffer, "%[^:]:%d", sensor, &value);

			// read signal
			if(strcmp(sensor, "UP") == 0) 
			{
				upDistance = value; 
			} 
			else if(strcmp(sensor, "FRONT") == 0) 
			{
				frontDistance = value; 
			} 
			else if(strcmp(sensor, "LUX") == 0) 
			{
				luxValue = value; 
			}
			else if(strcmp(sensor, "INFRAED") == 0)
			{
				infraedValue = value;
			}
			else if(strcmp(sensor, "JOY") == 0) 
			{
				joyValue = value;
			}
			
			index_buf = 0;
			memset(buffer, 0, sizeof(buffer)); // buffer
		}
	}
}
