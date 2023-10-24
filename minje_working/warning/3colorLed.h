#pragma once

#include <wiringPi.h>

#define Red_pin 22
#define Green_pin 27
#define Blue_pin 17

void init_3colorLed(){
    pinMode(Blue_pin, OUTPUT);
    pinMode(Green_pin, OUTPUT);
    pinMode(Red_pin, OUTPUT);
}

void turnRed(){
    digitalWrite(Blue_pin, LOW);
    digitalWrite(Green_pin, LOW);
    digitalWrite(Red_pin, HIGH);
}

void offRed(){
    digitalWrite(Red_pin, LOW);
}

void turnGreen(){
    digitalWrite(Blue_pin, LOW);
    digitalWrite(Green_pin, HIGH);
    digitalWrite(Red_pin, LOW);
}

void offGreen(){
    digitalWrite(Green_pin, LOW);
}

void turnBlue(){
    digitalWrite(Blue_pin, HIGH);
    digitalWrite(Green_pin, LOW);
    digitalWrite(Red_pin, LOW);
}

void offBlue(){
    digitalWrite(Blue_pin, LOW);
}