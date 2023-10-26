/* 
    [창문 서보모터 설정값]
        열린 상태 : 180
        닫힌 상태 : 5

    [추가 함수 종류]
        - void WindowControl_with_tunnelState()
            :   터널 안이면 창문 열거나 닫음.
        - void setAngleFast_Start_End(int angle_increase)
            :   현재 각도에서 원하는 각도만큼 이동함. 
                부호에 따라 방향 결정. 양수이면 반시계방향 회전, 음수이면 시계방향 회전
*/

#include "windowOpenClose.h"
int angle_current = 0;

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
    angle_current = angle;
}

void setAngleFast_Start_End(int angle_increase)
{
    setServo();
    pwmWrite(MOTOR_PIN, 20 + (angle_current + angle_increase) * MOTOR_PULSE);
    angle_current = angle_current + angle_increase;
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

    angle_current = end;
}

void WindowControl_with_tunnelState(){
    /* 터널 내/외부인지에 따라 창문을 열고 닫음 */
    int16_t flag_tunnel_in_out = determine_tunnel_in_out();
    if (flag_tunnel_in_out == 1) {          // In the tunnel. Close Window
        setAngleFast(5);
    }
    else if (flag_tunnel_in_out == 2) {     // Outside the tunnel. Open window
        setAngleFast(180);
    }
}

int main() {
    wiringPiSetupGpio();
    init_motor();

    /* 터널 내/외부인지에 따라 창문을 열고 닫음 */
    WindowControl_with_tunnelState();


    delay(1000);
    /* 현재 각도에서 원하는 각도만큼 더 움직이는 함수: setAngleFast_Start_End() */
    /* 0도로 이동한 후, 10도씩 점진적으로 열고 닫히게 하는 예제 */
    angle_current = 0;
    for(int i=0; i<17; i++){
        setAngleFast_Start_End(10);
        delay(300);
    }
    for(int i=0; i<17; i++){
        setAngleFast_Start_End(-10);
        delay(300);
    }

    return 0;
}