#include <SoftwareSerial.h>
//블루투스모듈 HC-06(슬래이브만가능)으로 진행함 
//블루투스모듈 HC-05(슬래이브 마스터둘다가능)는 조금 코드가 다르다  
//HC-06 시리얼창에서 "line ending 없음" 설정할것

int Tx = 6; //전송 보내는핀  
int Rx = 7; //수신 받는핀
int speaker = 2; //스피커 연결 핀

int buttonPin = 10; //택트 스위치 연결 핀
int ledPin = 5;     // LED 핀 설정
 
SoftwareSerial BtSerial(Tx,Rx);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("hello");
  BtSerial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(speaker, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BtSerial.available()) {       
    Serial.write(BtSerial.read());
  }
  if (Serial.available()) {         
    BtSerial.write(Serial.read());
  }
  
if (digitalRead(buttonPin) == LOW) {
    digitalWrite(ledPin, HIGH);
    tone(speaker, 440);
delay(700);
noTone(speaker);
delay(500);//계이름: 라
  } else {
    digitalWrite(ledPin, LOW);
  }

}
