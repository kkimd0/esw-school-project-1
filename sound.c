#include <stdio.h>
#include <wiringPi.h>

#define buzzer_pin 18

void init();
void setSound(); 
void finalSound();
void turnRed();
void offRed();
void turnGreen();
void offGreen();
void turnBlue();
void offBlue();

int main(void) 
{
    if (wiringPiSetup() == -1) {
        return 1;
    }

    init();

    turnGreen();

    delay(5000);

    for(int i=0;i<5;i++){
        finalSound();
    }
    
}

void init(){
    wiringPiSetupGpio();

    pinMode(buzzer_pin, PWM_OUTPUT);
    pwmSetClock(19);
    pwmSetMode(PWM_MODE_MS);

    pinMode(17, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(22, OUTPUT);
}

void setSound(){
    pwmSetRange(1000000/1174);
    pwmWrite(buzzer_pin, 1000000/1174/2);
}

void finalSound(){
    setSound();
    turnRed();
    delay(200);
    pwmWrite(buzzer_pin,0);
    offRed();
    delay(100);
    setSound();
    turnRed();
    delay(100);
    pwmWrite(buzzer_pin,0);
    offRed();
    delay(500);
}

void turnRed(){
    digitalWrite(17, LOW);
    digitalWrite(27, LOW);
    digitalWrite(22, HIGH);
}

void offRed(){
    digitalWrite(22, LOW);
}

void turnGreen(){
    digitalWrite(17, LOW);
    digitalWrite(27, HIGH);
    digitalWrite(22, LOW);
}

void offGreen(){
    digitalWrite(27, LOW);
}

void turnBlue(){
    digitalWrite(17, HIGH);
    digitalWrite(27, LOW);
    digitalWrite(22, LOW);
}

void offBlue(){
    digitalWrite(17, LOW);
}