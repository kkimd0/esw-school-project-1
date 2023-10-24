#packages:
#        [ -z `dpkg -l | grep git` ] && sudo apt-get install git
#.PHONY: packages

CC= gcc
CFLAGS= -W -Wall -I/usr/local/include
TARGET= run
LDLIBS = -lwiringPi
OBJECTS = $(CURDIR)/step_motor/step_motor.o main.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@
	
step_motor.o: step_motor.c
	$(CC) $(CFLAGS) -o $(CURDIR)/step_motor/step_motor.o -c $(CURDIR)/step_motor/step_motor.c
	
main.o: main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)