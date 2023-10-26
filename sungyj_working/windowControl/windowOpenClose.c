#include "windowOpenClose.h"

void init_motor()
{
    pinMode ( MOTOR_PIN ,  PWM_OUTPUT ); 
    pwmSetMode ( PWM_MODE_MS ); 
}

void setServo()
{
    pwmSetClock ( 384 ); 
    pwmSetRange ( 1000 );
}

void setAngleFast(int angle)
{
    setServo();
    pwmWrite(MOTOR_PIN, 20 + angle * MOTOR_PULSE);
}

void setAngleSlow(int start, int end)
{
    setServo();

    if(start <= end){
        for(int i = start * MOTOR_PULSE; i <= end * MOTOR_PULSE; i++){
            pwmWrite(MOTOR_PIN, i + 20);
            delay(20);
        }
    }
    else
    {
        for(int i = start * MOTOR_PULSE; i >= end * MOTOR_PULSE; i--){
            pwmWrite(MOTOR_PIN, i + 20);
            delay(20);
        }
    }
}

int main() {
    wiringPiSetupGpio();
    init_motor();

    int16_t flag_tunnel_in_out = determine_tunnel_in_out();
    if (flag_tunnel_in_out == 1) {
        setAngleFast(180);
    }
    else if (flag_tunnel_in_out == 2) {
        setAngleFast(0);
    }

    return 0;
}