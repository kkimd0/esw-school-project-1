#packages:
#        [ -z `dpkg -l | grep git` ] && sudo apt-get install git
#.PHONY: packages

CC= gcc
CFLAGS= -W -Wall -I/usr/local/include
TARGET= run
LDLIBS = -lwiringPi
OBJECTS = main.o $(CURDIR)/step_motor/step_motor.o $(CURDIR)/minje_working/motor/servo_motor.o \
		  $(CURDIR)/minje_working/warning/buzzer.o $(CURDIR)/minje_working/warning/3colorLed.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@
	
step_motor.o: step_motor.c
	$(CC) $(CFLAGS) -o $(CURDIR)/step_motor/step_motor.o -c $(CURDIR)/step_motor/step_motor.c
	
servo_motor.o: servo_motor.c
	$(CC) $(CFLAGS) -o $(CURDIR)/minje_working/motor/servo_motor.o -c $(CURDIR)/minje_working/motor/servo_motor.c

buzzer.o: buzzer.c
	$(CC) $(CFLAGS) -o $(CURDIR)/minje_working/warning/buzzer.o -c $(CURDIR)/minje_working/warning/buzzer.c

3colorLed.o: 3colorLed.c
	$(CC) $(CFLAGS) -o $(CURDIR)/minje_working/warning/3colorLed.o -c $(CURDIR)/minje_working/warning/3colorLed.c
	
main.o: main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)