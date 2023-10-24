#include "3colorLed.h"

void init_3colorLed()
{
    pinMode(BLUE_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(RED_PIN, OUTPUT);
}

void turnRed()
{
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
}

void offRed()
{
    digitalWrite(RED_PIN, LOW);
}

void turnGreen()
{
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(RED_PIN, LOW);
}

void offGreen()
{
    digitalWrite(GREEN_PIN, LOW);
}

void turnBlue()
{
    digitalWrite(BLUE_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, LOW);
}

void offBlue()
{
    digitalWrite(BLUE_PIN, LOW);
}