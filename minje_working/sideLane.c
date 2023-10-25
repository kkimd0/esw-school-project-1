#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include "warning/buzzer.h"
#include "warning/3colorLed.h"

void *pthread_ex();

int joyValue = 500;

int main()
{
    wiringPiSetupGpio();

    init_buzzer();
    init_3colorLed();
    
    turnGreen();

    int sts;
    pthread_t thread_id;
    void* t_return;

    if((sts = pthread_create((&thread_id), NULL, pthread_ex, NULL)) != 0){
        perror("multi thread error!\n");
        exit(1);
    }

    while(1){

        if(joyValue  >= 750){
            sideLaneWarningSound();
        }else if(joyValue  <= 250){
            sideLaneWarningSound();
        }else{
            turnGreen();
        }
    }
}

void *pthread_ex(){
    char input;

    while(1){
        printf("current value : %d, input the direction(l / r) : ", joyValue);
        scanf(" %c", &input);
        printf("%c\n", input);

        if(input == 'l'){
            joyValue = joyValue - 20;
        }else{
            joyValue = joyValue + 20;
        }
    }
}