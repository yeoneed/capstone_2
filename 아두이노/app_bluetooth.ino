#include <SoftwareSerial.h>
//블루투스모듈 HC-06(슬래이브만가능)으로 진행함 
//블루투스모듈 HC-05(슬래이브 마스터둘다가능)는 조금 코드가 다르다  
//HC-06 시리얼창에서 "line ending 없음" 설정할것

int Tx = 6; //전송 보내는핀  
int Rx = 7; //수신 받는핀
int speaker = 2; //스피커 연결 핀

int buttonPin = 10; //택트 스위치 연결 핀
SoftwareSerial BtSerial(Tx,Rx);

char incomingByte;  // incoming data
int  LED = 5;      // LED pin

void setup() {
  Serial.begin(9600); // initialization
  Serial.println("hello");
  BtSerial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(speaker, OUTPUT);
  Serial.println("Press 1 to LED ON or 0 to LED OFF...");
}

void loop() {

if (digitalRead(buttonPin) == LOW) {
    digitalWrite(LED, HIGH);
    Serial.println("버튼 PUSH: LED ON");
    tone(speaker, 440);
    delay(700);
    noTone(speaker);
    delay(500);//계이름: 라
  } else {
    digitalWrite(LED, LOW);
  }
  
  if (BtSerial.available() > 0) {  // if the data came
    incomingByte = BtSerial.read(); // read byte
    if(incomingByte == '0') {
       digitalWrite(LED, LOW);  // if 1, switch LED Off
       Serial.println("LED OFF. Press 1 to LED ON!");  // print message
    }
    if(incomingByte == '1') {
       digitalWrite(LED, HIGH); // if 0, switch LED on
       Serial.println("앱 PUSH: LED ON. Press 0 to LED OFF!");
       tone(speaker, 440);
       delay(700);
       noTone(speaker);
       // delay(500);//계이름: 라
    }
  }
    
}
