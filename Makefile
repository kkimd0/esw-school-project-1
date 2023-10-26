#packages:
#        [ -z `dpkg -l | grep git` ] && sudo apt-get install git
#.PHONY: packages

CC= gcc
CFLAGS= -W -Wall
TARGET= run
LDLIBS = -lpthread -lwiringPi -DRaspberryPi
OBJECTS = main.o $(CURDIR)/step_motor/step_motor.o $(CURDIR)/minje_working/motor/servo_motor.o \
	  $(CURDIR)/minje_working/warning/buzzer.o $(CURDIR)/minje_working/warning/3colorLed.o \
	  sensor.o $(CURDIR)/sungyj_working/LCD.o

$(TARGET): $(OBJECTS)
	sudo $(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

step_motor.o: step_motor.c
	$(CC) $(CFLAGS) -o $(CURDIR)/step_motor/step_motor.o -c $(CURDIR)/step_motor/step_motor.c

servo_motor.o: servo_motor.c
	$(CC) $(CFLAGS) -o $(CURDIR)/minje_working/motor/servo_motor.o -c $(CURDIR)/minje_working/motor/servo_motor.c

buzzer.o: buzzer.c
	$(CC) $(CFLAGS) -o $(CURDIR)/minje_working/warning/buzzer.o -c $(CURDIR)/minje_working/warning/buzzer.c

3colorLed.o: 3colorLed.c
	$(CC) $(CFLAGS) -o $(CURDIR)/minje_working/warning/3colorLed.o -c $(CURDIR)/minje_working/warning/3colorLed.c

LCD.o: LCD.c
	$(CC) $(CFLAGS) -o $(CURDIR)/sungyj_working/LCD.o -c $(CURDIR)/sungyj_working/LCD.c

sensor.o: sensor.c
	$(CC) $(CFLAGS) -o sensor.o -c sensor.c

main.o: main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -f $(CURDIR)/main.o
	rm -f $(CURDIR)/sensor.o
	rm -f $(CURDIR)/step_motor/step_motor.o 
	rm -f $(CURDIR)/minje_working/motor/servo_motor.o
	rm -f $(CURDIR)/minje_working/warning/buzzer.o
	rm -f $(CURDIR)/minje_working/warning/3colorLed.o
	rm -f $(CURDIR)/sungyj_working/LCD.o
	rm -f $(TARGET)

