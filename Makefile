
CC= gcc
CFLAGS= -W -Wall
TARGET= run
LDLIBS = -lpthread -lwiringPi -DRaspberryPi
OBJECTS = $(CURDIR)/src/main.o $(CURDIR)/src/step_motor.o $(CURDIR)/src/servo_motor.o \
	  $(CURDIR)/src/buzzer.o $(CURDIR)/src/3colorLed.o $(CURDIR)/src/LCD.o \
	  $(CURDIR)/src/sensor.o

$(TARGET): $(OBJECTS)
	sudo $(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

step_motor.o: step_motor.c
	$(CC) $(CFLAGS) -o $(CURDIR)/src/step_motor.o -c $(CURDIR)/src/step_motor.c

servo_motor.o: servo_motor.c
	$(CC) $(CFLAGS) -o $(CURDIR)/src/servo_motor.o -c $(CURDIR)/src/servo_motor.c

buzzer.o: buzzer.c
	$(CC) $(CFLAGS) -o $(CURDIR)/src/buzzer.o -c $(CURDIR)/src/buzzer.c

3colorLed.o: 3colorLed.c
	$(CC) $(CFLAGS) -o $(CURDIR)/src/3colorLed.o -c $(CURDIR)/src/3colorLed.c

LCD.o: LCD.c
	$(CC) $(CFLAGS) -o $(CURDIR)/src/LCD.o -c $(CURDIR)/src/LCD.c

sensor.o: sensor.c
	$(CC) $(CFLAGS) -o $(CURDIR)/src/sensor.o -c $(CURDIR)/src/sensor.c

main.o: main.c
	$(CC) $(CFLAGS) -o $(CURDIR)/src/main.o -c $(CURDIR)/src/main.c

clean:
	rm -f $(CURDIR)/src/main.o
	rm -f $(CURDIR)/src/sensor.o
	rm -f $(CURDIR)/src/step_motor.o 
	rm -f $(CURDIR)/src/servo_motor.o
	rm -f $(CURDIR)/src/buzzer.o
	rm -f $(CURDIR)/src/3colorLed.o
	rm -f $(CURDIR)/src/LCD.o
	rm -f $(TARGET)

