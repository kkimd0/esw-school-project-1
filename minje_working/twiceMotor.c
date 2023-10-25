#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include "step_motor/step_motor.h"
#include "motor/servo_motor.h"

void *pthread_ex();
void *pthread_ex2();

int main(){
    
    wiringPiSetupGpio();

    init_motor();
    init_step_motor();

    pinMode(20, OUTPUT);                     
    pinMode(21, INPUT);

    int distance = 0;
    int start = 0;
    int stop = 0;

    int ang = 0;


    while(1){
        digitalWrite(20, LOW);
        digitalWrite(20, HIGH);

        delay(10);
        digitalWrite(20, LOW);

        while(digitalRead(21) == 0){
            start = micros();
        }

        while(digitalRead(21) == 1){
            stop = micros();
        }

        distance = (stop - start) / 58;
        printf("Distance : %d\n", distance);

        if (distance < 20){
            int sts;
            pthread_t thread_id;
            void* t_return;

            if((sts = pthread_create((&thread_id), NULL, pthread_ex, NULL)) != 0){
                perror("1multi thread error!\n");
                exit(1);
            }
            printf("thread id : %d", thread_id);
            
            if((sts = pthread_create((&thread_id), NULL, pthread_ex2, NULL)) != 0){
                perror("2multi thread error!\n");
                exit(1);
            }
        }

        delay(100);
    }
    
}

void *pthread_ex(){
    one_cycle_rotation();
}

void *pthread_ex2(){
    angle(0, 180);
}
