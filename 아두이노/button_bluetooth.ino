#include <SoftwareSerial.h>
//블루투스모듈 HC-06(슬래이브만가능)으로 진행함 
//블루투스모듈 HC-05(슬래이브 마스터둘다가능)는 조금 코드가 다르다  
//HC-06 시리얼창에서 "line ending 없음" 설정할것

int Tx = 6; //전송 보내는핀  
int Rx = 7; //수신 받는핀

int sw = 10;       // 스위치(SW) 핀 설정
int led = 5;       // LED 핀 설정
 
int state = LOW;      // LED 상태
int reading;          // SW 상태
int previous = LOW;   // SW 이전 상태
 
long time = 0;        // LED가 ON/OFF 토글된 마지막 시간
long debounce = 100;  // Debounce 타임 설정

SoftwareSerial BtSerial(Tx,Rx);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("hello");
  BtSerial.begin(9600);

pinMode(sw, INPUT_PULLUP); // SW 를 설정, 아두이노 풀업저항 사용
  pinMode(led, OUTPUT);      // LED 설정
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BtSerial.available()) {       
    Serial.write(BtSerial.read());
  }
  if (Serial.available()) {         
    BtSerial.write(Serial.read());
  }
reading = digitalRead(sw);  // SW 상태 읽음
 
  //SW 가 눌려졌고 스위치 토글 눌림 경과시간이 Debounce 시간보다 크면 실행
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)    // LED 가 HIGH 면 LOW 로 바꿔준다.
      state = LOW;
    else                  // LED 가 LOW 면 HIGH 로 바꿔준다.
      state = HIGH;
 
    time = millis();
  }
 
  digitalWrite(led, state);
 
  previous = reading;

}
