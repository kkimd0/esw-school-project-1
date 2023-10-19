#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h> 

#define SERVO 1

int main()
{
    char sel;

    if(wiringPiSetup()==-1)
        return 1;

    softPwmCreate(SERVO, 0, 2000);

    while(1)
    {   
        fputs("select c, r, l, q: " , stdout);
        scanf("%c" , &sel);
        getchar();
        if(sel == 'c') softPwmWrite(SERVO, 5);   // 0 degree
        else if(sel == 'r') softPwmWrite(SERVO, 10); // 90 degree
        else if(sel == 'l') softPwmWrite(SERVO, 7); // -90 degree
        else if(sel == 'q') return 0;
    }   

    return 0;
}
