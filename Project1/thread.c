#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include <wiringPi.h>
// #include <wiringPiSerial.h>

#define RED 2
#define BLUE 3

void setup() {
  wiringPiSetupGPIO();
  wiringPiSetup();

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void* function_A(void* num){
  while(1){
    digitalWrite(RED, HIGH);
    sleep(1);
    digitalWrite(BLUE, LOW);
  }
}

void* function_B(void* num){
  while(1){
    digitalWrite(BLUE, HIGH);
    sleep(3);
    digitalWrite(RED, LOW);
  }
}
int main(){

  setup();
	
  pthread_t pthread_A,pthread_B;
  int cnt=0;

  //thread A를 생성
  pthread_create(&pthread_A, NULL, function_A, NULL);

  //thread B를 생성
  pthread_create(&pthread_B, NULL, function_B, NULL);	
  
  return 1;
}
