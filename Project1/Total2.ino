#include <IRremote.hpp>

#define luxPin 14
#define remotePin 15

#define upTrigPin 8
#define upEchoPin 2

#define frontTrigPin 9
#define frontEchoPin 3

#define joyStick_Z_Pin 16

uint32_t luxValue;
uint32_t Infraed_message;
uint32_t upDistance;
uint32_t frontDistance;
uint32_t joyValueZ;

uint32_t time_Ultra;
uint32_t time_Lux;

uint8_t goUp = 1;
uint8_t goDown = 0;
volatile uint8_t interruptMode_up = goUp;    // 맨 처음에는 echo_phin이 LOW->HIGH로 바뀌는거 감지해야됨 
volatile boolean timeMeasure_up = false;    // 시간측정이 완료되었는지 여부 
volatile uint32_t startT_up, endT_up ;    //echo_phin  상승시간과  하강시간  저장 변수

volatile uint8_t interruptMode_front = goUp;    // 맨 처음에는 echo_phin이 LOW->HIGH로 바뀌는거 감지해야됨 
volatile boolean timeMeasure_front = false;    // 시간측정이 완료되었는지 여부 
volatile uint32_t startT_front, endT_front ;    //echo_phin  상승시간과  하강시간  저장 변수

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  IrReceiver.begin(remotePin, ENABLE_LED_FEEDBACK);    //IRReceiver 초기설정
  
  attachInterrupt(digitalPinToInterrupt(upEchoPin), soundDetection_up, RISING);
  attachInterrupt(digitalPinToInterrupt(frontEchoPin), soundDetection_front, RISING);

  pinMode(luxPin, INPUT);

  pinMode(upTrigPin, OUTPUT);
  pinMode(upEchoPin, INPUT);

  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);

  pinMode(joyStick_Z_Pin, INPUT);
}

void loop() {

  /* Ultra Sensor */
  if(millis() - time_Ultra > 1000) {  //2초 이상 이면
    time_Ultra = millis() ; //현재 시간을 이전시간에 저장
    attachInterrupt(digitalPinToInterrupt(upEchoPin), soundDetection_up, RISING);   // 하강에지로 설정되어있을 경우  다시 상승에지로 바꿔주기 
    attachInterrupt(digitalPinToInterrupt(frontEchoPin), soundDetection_front, RISING);
    
    digitalWrite(upTrigPin, LOW); // 일단 LOW, 좀있다 HIGH로 바꿔줘서 펄스 발생 
    digitalWrite(frontTrigPin, LOW);
    delayMicroseconds(100);
    
    digitalWrite(upTrigPin, HIGH);   // 펄스 발생  100us 동안
    digitalWrite(frontTrigPin, HIGH);
    delayMicroseconds(100);
    
    digitalWrite(upTrigPin, LOW); // 일단 LOW, 좀있다 HIGH로 바꿔줘서 펄스 발생 
    digitalWrite(frontTrigPin, LOW);
 }

 if(timeMeasure_up) { // 시간측정이 완료되었다면 
  uint32_t duration = endT_up - startT_up;            //echo_pin이 발생한 HIGH였던 시간 측정 (echo_pin)은 거리가 길수록 HIGH를 오랫동안 유지 
  upDistance = ((340 * duration) / 10000) / 2; // 천장거리 저장
//  upDistance = normalize(upDistance, 0, 255);
  String value = String(upDistance);
  Serial.print("UP:");
  Serial.print(value);
  Serial.print("q");
  timeMeasure_up = false;  //다음 번 측정을 위해 초기화
 }

 if(timeMeasure_front) { // 시간측정이 완료되었다면 
  uint32_t duration = endT_front - startT_front;            //echo_pin이 발생한 HIGH였던 시간 측정 (echo_pin)은 거리가 길수록 HIGH를 오랫동안 유지 
  frontDistance = ((340 * duration) / 10000) / 2; // 앞차와의 거리 저장
//  frontDistance = normalize(frontDistance, 0, 255);
  String value = String(frontDistance);
  Serial.print("FRONT:");
  Serial.print(value);
  Serial.print("q");
  timeMeasure_front = false;  //다음 번 측정을 위해 초기화
 }



 /* Lux Sensor */
 if(millis() - time_Lux > 1000) {  //2초 이상 이면
  time_Lux = millis() ; //현재 시간을 이전시간에 저장
  luxValue = analogRead(luxPin);
  String value = String(luxValue);
//  luxValue = normalize(luxValue, 0, 1500);
  Serial.print("LUX:");
  Serial.print(value);
  Serial.print("q");
 }

 

 /* Infrared Sensor */
 if(IrReceiver.decode())
 {
  uint32_t IrRawData = IrReceiver.decodedIRData.decodedRawData;
  //Switch - Case문 작성 필요
  switch(IrRawData) {
    case 0xF30CFF00 :
      Infraed_message = 10;
      break;
    case 0xE718FF00 :
      Infraed_message = 20;
      break;
    case 0xA15EFF00 :
      Infraed_message = 30;
      break;
    case 0 :
      ;
    default :
      
  }

  Serial.print("INFRAED:");
  Serial.print(Infraed_message);
  Serial.print("q");
  
  IrReceiver.resume();
 }




 /* joyStick Sensor */
  joyValueZ = analogRead(joyStick_Z_Pin);
  Serial.print("JOY:");
  Serial.print(joyValueZ);
  Serial.print("q");
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
}
