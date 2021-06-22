#include <SoftwareSerial.h>   // 引用程式庫
//#include <Wire.h> //引用二個函式庫SoftwareSerial及Wire SoftwareSerial 
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(12, 3); // 接收腳, 傳送腳
char cmd;
byte motorSpeed;
byte RmotorSpeed;
byte LmotorSpeed;
// Speed Set
byte InitialSpeed = 80;
byte Balance = 0;//50
byte turnSpeed = 80;

//LEFT
const byte R1 = 8; //IN1
const byte R2 = 9; //IN2
const byte R_PWM = 10;
//RIGHT
const byte L1 = 7; //IN3
const byte L2 = 6; //IN4
const byte L_PWM = 5;
void forward() {
  RmotorSpeed = motorSpeed;
  LmotorSpeed = RmotorSpeed+ Balance;
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  analogWrite(R_PWM, RmotorSpeed);

  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  analogWrite(L_PWM, LmotorSpeed);
}
void backward() {
  //LEFT WHEEL
  RmotorSpeed = motorSpeed;
  LmotorSpeed = RmotorSpeed+ Balance;
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  analogWrite(R_PWM, RmotorSpeed);
  //RIGHT WHEEL
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  analogWrite(L_PWM, LmotorSpeed);
}
void turnLeft() {
  RmotorSpeed = motorSpeed;
  LmotorSpeed = RmotorSpeed+Balance;
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  analogWrite(R_PWM, (RmotorSpeed));
  //analogWrite(R_PWM, 0);
  
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  analogWrite(L_PWM, LmotorSpeed - (turnSpeed+Balance));
}

void turnRight() {
  RmotorSpeed = motorSpeed;
  LmotorSpeed = RmotorSpeed+Balance;
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  analogWrite(L_PWM, LmotorSpeed);
  
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  analogWrite(R_PWM, RmotorSpeed - turnSpeed);
}
void stopMotor() {
  analogWrite(R_PWM, 0);
  analogWrite(L_PWM, 0);
}
void setup() {
  Serial.begin(9600);
  BT.begin(38400);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L_PWM, OUTPUT);
}

void loop() {
  Balance = 0;
  if (BT.available()){
      cmd = BT.read();    
        switch(cmd){
          case 'w':
            forward();
            break;
          case 'x':
            backward();
            break;
          case 'a':
            turnRight();
            break;
          case 'd':
            turnLeft();
            break;
          case 's':
            stopMotor();
            break;  
          case 'A':
            motorSpeed = InitialSpeed;
            motorSpeed = motorSpeed+20;
            Balance = 10;
            break;   
          case 'B':
            motorSpeed = InitialSpeed;
            motorSpeed = motorSpeed+40;
            Balance = 15;
            break;      
          case 'C':
            motorSpeed = InitialSpeed;
            motorSpeed = motorSpeed+60;
            Balance = 20;
            break;    
          case 'D':
            motorSpeed = InitialSpeed;
            motorSpeed = motorSpeed+80;
            Balance = 25;
            break;  
          case 'E':
            motorSpeed = InitialSpeed;
            motorSpeed = motorSpeed+100;
            Balance = 30;
            break;    
          case '1':
            Serial.print('1');


      }  
      
    }
}
