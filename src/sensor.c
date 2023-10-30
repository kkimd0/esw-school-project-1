#include "sensor.h"

static uint32_t fd;
uint32_t upDistance = 0;
uint32_t frontDistance = 0;
uint32_t luxValue = 0;
uint32_t infraredValue = 0;
uint32_t joyValue = 0;

int8_t servo_motor_flag;
int8_t step_motor_flag;
int8_t buzzer_flag;
int8_t infrared_flag;

enum CarState carState;

int8_t init_sensor()
{
	//get filedescriptor
	fd = 0;
	
	fd = serialOpen (DEVICE, SERIALBAUD);
	if ( fd < 0 )
	{
		printf ("Unable to open serial device\n");
	}
	
	return fd;
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
				infraredValue = value;
			}
			else if(strcmp(sensor, "JOY") == 0) 
			{
				joyValue = value;
			}
			else
			{
				;
			}
			
			index_buf = 0;
			memset(buffer, 0, sizeof(buffer)); // buffer
		}
	}
}

void *infrared_contorl()
{
	usleep(500000);
	infrared_flag = 0;
}
