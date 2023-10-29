#include <IRremote.hpp>

#define luxPin 14
#define remotePin 15

#define upTrigPin 8
#define upEchoPin 2

#define frontTrigPin 9
#define frontEchoPin 3

#define joyStick_Z_Pin 16

uint32_t luxValue;
uint32_t infrared_message;
uint32_t upDistance;
uint32_t frontDistance;
uint32_t joyValueZ;
uint32_t time_Ultra;

uint8_t goUp = 1;
uint8_t goDown = 0;

volatile uint8_t interruptMode_up = goUp;    // 맨 처음에는 echo_phin이 LOW->HIGH로 바뀌는거 감지해야됨 
volatile boolean timeMeasure_up = false;    // 시간측정이 완료되었는지 여부 
volatile uint32_t startT_up, endT_up ;    //echo_phin  상승시간과  하강시간  저장 변수

volatile uint8_t interruptMode_front = goUp;    // 맨 처음에는 echo_phin이 LOW->HIGH로 바뀌는거 감지해야됨 
volatile boolean timeMeasure_front = false;    // 시간측정이 완료되었는지 여부 
volatile uint32_t startT_front, endT_front ;    //echo_phin  상승시간과  하강시간  저장 변수

String letter = "~";

void gpioInit();

void soundDetection_up();
void soundDetection_front();

void readUltraSensor();
void readLuxSensor();
void readInfraredSensor();
void readJoyStickSensor();
void sendSignal(String str, uint32_t val);

void setup() {
  Serial.begin(9600);

  IrReceiver.begin(remotePin, ENABLE_LED_FEEDBACK);    //IRReceiver 초기설정
  
  attachInterrupt(digitalPinToInterrupt(upEchoPin), soundDetection_up, RISING);
  attachInterrupt(digitalPinToInterrupt(frontEchoPin), soundDetection_front, RISING);

  gpioInit();
}

void loop() {
  readUltraSensor();
  readLuxSensor();
  readInfraredSensor();
  readJoyStickSensor();
  
  delay(50);
}


void gpioInit()
{
  pinMode(luxPin, INPUT);

  pinMode(upTrigPin, OUTPUT);
  pinMode(upEchoPin, INPUT);

  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);

  pinMode(joyStick_Z_Pin, INPUT);
}


void sendSignal(String str, uint32_t val) {
  String value = String(val);
  Serial.print(str);
  Serial.print(value);
  Serial.print(letter);
}


/* Ultra Sensor */
void readUltraSensor() {
  if((millis() - time_Ultra) > 1000) {  //2초 이상 이면
      time_Ultra = millis() ; //현재 시간을 이전시간에 저장
      attachInterrupt(digitalPinToInterrupt(upEchoPin), soundDetection_up, RISING);   // 하강에지로 설정되어있을 경우  다시 상승에지로 바꿔주기 
      attachInterrupt(digitalPinToInterrupt(frontEchoPin), soundDetection_front, RISING);
      
      digitalWrite(upTrigPin, LOW); // 일단 LOW, 좀있다 HIGH로 바꿔줘서 펄스 발생 
      digitalWrite(frontTrigPin, LOW);
      delayMicroseconds(10);
      
      digitalWrite(upTrigPin, HIGH);   // 펄스 발생  10us 동안
      digitalWrite(frontTrigPin, HIGH);
      delayMicroseconds(10);
      
      digitalWrite(upTrigPin, LOW); // 일단 LOW, 좀있다 HIGH로 바꿔줘서 펄스 발생 
      digitalWrite(frontTrigPin, LOW);
  }

  if(timeMeasure_up) { // 시간측정이 완료되었다면 
      uint32_t duration = endT_up - startT_up;            //echo_pin이 발생한 HIGH였던 시간 측정 (echo_pin)은 거리가 길수록 HIGH를 오랫동안 유지 
      upDistance = ((340 * duration) / 10000) / 2; // 천장거리 저장
      
      uint8_t flag = 0;
      if(upDistance < 0) {
        flag = 1;
      }
      
      // 오류가 나지 않았을 때만 값 전송
      if(flag == 0) {
        sendSignal("UP:", upDistance);
      }
      timeMeasure_up = false;  //다음 번 측정을 위해 초기화
  }

  if(timeMeasure_front) { // 시간측정이 완료되었다면 
      uint32_t duration = endT_front - startT_front;            //echo_pin이 발생한 HIGH였던 시간 측정 (echo_pin)은 거리가 길수록 HIGH를 오랫동안 유지 
      frontDistance = ((340 * duration) / 10000) / 2; // 앞차와의 거리 저장
      
      uint8_t flag = 0;
      if(frontDistance < 0) {
        flag = 1;
      }
      
      // 오류가 나지 않았을 때만 값 전송
      if(flag == 0) {
        sendSignal("FRONT:", frontDistance);
      }
      timeMeasure_front = false;  //다음 번 측정을 위해 초기화
  }
}


/* Lux Sensor */
void readLuxSensor() {
  luxValue = analogRead(luxPin);
  
  uint8_t flag = 0;
  if(luxValue < 0) {
    flag = 1;
  }
  
  // 오류가 나지 않았을 때만 값 전송
  if(flag == 0) {
    sendSignal("LUX:", luxValue);
  }
}


/* Infrared Sensor */
void readInfraredSensor() {
  if(IrReceiver.decode())
  {
      uint32_t IrRawData = IrReceiver.decodedIRData.decodedRawData;
      //Switch - Case문 작성 필요
      switch(IrRawData) {
        case 0xF30CFF00 :
          infrared_message = 10;
          break;
        case 0xE718FF00 :
          infrared_message = 20;
          break;
        case 0xA15EFF00 :
          infrared_message = 30;
          break;
        default :
          infrared_message = 0;
      }

      sendSignal("INFRAED:", infrared_message);
      
      IrReceiver.resume();
  }
  else {
      infrared_message = 0;
      
      sendSignal("INFRAED:", infrared_message);
  }
}


/* Joy Sensor */
void readJoyStickSensor() {
  joyValueZ = analogRead(joyStick_Z_Pin);
  
  uint8_t flag = 0;
  if(joyValueZ < 0) {
    flag = 1;
  }
  
  // 오류가 나지 않았을 때만 값 전송
  if(flag == 0) {
    sendSignal("JOY:", joyValueZ);
  }
}


void soundDetection_up() {
  if(interruptMode_up == goUp){  //상승에지를 감지 했으면
    interruptMode_up = goDown;  //이번엔 하강에지를 감지해보자
    startT_up = micros(); //인터룹트함수에서 millis사용 불가,  시작시간 저장 
    attachInterrupt(digitalPinToInterrupt(upEchoPin), soundDetection_up, FALLING);   //다음에는 하강에지를 감지해보자 
  }
  else if(interruptMode_up == goDown){ //하강에지를 감지했으면 
    interruptMode_up = goUp;  //이번엔 하강에지를 감지해보자 
    endT_up = micros(); //인터룹트함수에서 millis사용 불가, // 끝나는 시간 저장 
    timeMeasure_up = true;  //하강에지로 왔다는건 시간 측정 끝 
    attachInterrupt(digitalPinToInterrupt(upEchoPin), soundDetection_up, RISING); //다음에는 상승에지를 감지해보자 
  }
  else {
    ;
  }
}


void soundDetection_front() {
  if(interruptMode_front == goUp){  //상승에지를 감지 했으면
    interruptMode_front = goDown;  //이번엔 하강에지를 감지해보자
    startT_front = micros(); //인터룹트함수에서 millis사용 불가,  시작시간 저장 buffer[inde
    attachInterrupt(digitalPinToInterrupt(frontEchoPin), soundDetection_front, FALLING);   //다음에는 하강에지를 감지해보자 
  }
  else if(interruptMode_front == goDown){ //하강에지를 감지했으면 
    interruptMode_front = goUp;  //이번엔 하강에지를 감지해보자 
    endT_front = micros(); //인터룹트함수에서 millis사용 불가, // 끝나는 시간 저장 
    timeMeasure_front = true;  //하강에지로 왔다는건 시간 측정 끝 
    attachInterrupt(digitalPinToInterrupt(frontEchoPin), soundDetection_front, RISING); //다음에는 상승에지를 감지해보자 
  }
  else {
    ;
  }
}
