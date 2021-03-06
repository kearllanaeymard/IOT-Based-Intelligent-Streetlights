#include<SoftwareSerial.h>
SoftwareSerial mySerial(11, 3);

int ldr = analogRead(A0);
int light1 = 5;
int light2 = 6;
int light3 = 7;

char inputData;
boolean newData = false;
int x = 0;
int y,z,r,s;

const  int trigger1 = 30; 
const  int echo1 = 31;
const  int trigger2 = 32; 
const  int echo2 = 33;
const  int trigger3 = 34; 
const  int echo3 = 35;
float  distance1, distance2, distance3;

unsigned long previousTime1 = 0;
unsigned long previousTime2 = 0;
unsigned long previousTime3 = 0;
unsigned long ledInterval = 5000;

void receiveInput(){
    if(mySerial.available()){
        inputData = mySerial.read();
        newData = true;
      }
  }

void showInput(){
    if(newData == true){
        Serial.println(inputData);
        newData = false;
      }
  }

void ping1(){
    digitalWrite(trigger1,LOW);
    delayMicroseconds(5);
    digitalWrite(trigger1,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger1,LOW);
    distance1 = pulseIn(echo1,HIGH);
    distance1 = distance1*0.0001657;
  }
void ping2(){
    digitalWrite(trigger2,LOW);
    delayMicroseconds(5);
    digitalWrite(trigger2,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger2,LOW);
    distance2 = pulseIn(echo2,HIGH);
    distance2 = distance2*0.0001657;
  }
void ping3(){
    digitalWrite(trigger3,LOW);
    delayMicroseconds(5);
    digitalWrite(trigger3,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger3,LOW);
    distance3 = pulseIn(echo3,HIGH);
    distance3 = distance3*0.0001657;
  }

void ping1Detected(){
    Serial.println("Ping1 Detected!");
    analogWrite(light1, 255);
    Serial.print("Ping1: ");
    Serial.println(distance1);
    mySerial.write('A');
    mySerial.write("o");
    while(z == 0){
        ping1();
        if(distance1 > 0.70){
          previousTime1 = millis();
          Serial.print("Prev Time1: ");
          Serial.println(millis());
          Serial.print("distance1: ");
          Serial.println(distance1);
          Serial.println("Data Recorded Successfully Light A");
          z++;
        }
        if((millis() - previousTime2) > ledInterval){
              analogWrite(light2, 4);
        }
        if((millis() - previousTime3) > ledInterval){
              analogWrite(light3, 4);
        }
      }
    
  }

void ping2Detected(){
    Serial.println("Ping2 Detected!");
    analogWrite(light2, 255);
    Serial.print("Ping2: ");
    Serial.println(distance2);
    mySerial.write('B');
    mySerial.write("o");
    while(r == 0){
        ping2();
        if(distance2 > 0.70){
          previousTime2 = millis();
          Serial.print("Prev Time2: ");
          Serial.println(millis());
          Serial.print("distance2: ");
          Serial.println(distance2);
          Serial.println("Data Recorded Successfully Light B");
          r++;
        }
        if((millis() - previousTime1) > ledInterval){
              analogWrite(light1, 4);
        }
        if((millis() - previousTime3) > ledInterval){
              analogWrite(light3, 4);
        }
      }  
  }

void ping3Detected(){
    Serial.println("Ping3 Detected!");
    analogWrite(light3, 255);
    Serial.print("Ping3: ");
    Serial.println(distance3);
    mySerial.write('C');
    mySerial.write("o");
    while(s == 0){
        ping3();
        if(distance3 > 0.70){
          previousTime3 = millis();
          Serial.print("Prev Time3: ");
          Serial.println(millis());
          Serial.print("distance3: ");
          Serial.println(distance3);
          Serial.println("Data Recorded Successfully Light C");
          s++;
        }
        if((millis() - previousTime1) > ledInterval){
              analogWrite(light1, 4);
        }
        if((millis() - previousTime2) > ledInterval){
              analogWrite(light2, 4);
        }
      }
  }

void streetlightsActivated(){
    mySerial.write('N');
    mySerial.write("o");
  }

void streetlightsDeactivated(){
    mySerial.write('F');
    mySerial.write("o");    
  }

void setup() {
  pinMode(trigger1,OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trigger2,OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trigger3,OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(52,OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);

  analogWrite(light1, 0);
  analogWrite(light2, 0);
  analogWrite(light3, 0);
  
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Arduino is Ready!");
  while(x == 0){
    receiveInput();
    showInput();
    if(inputData == 'X'){
      digitalWrite(52, HIGH);
      Serial.println("Hello from ESP");
      inputData = 'o';
      x++;
    }
  }
  delay(100);
  digitalWrite(52, LOW);
  delay(100);
  digitalWrite(52, HIGH);
  delay(100);
  digitalWrite(52, LOW);
}


void loop() {
  // put your main code here, to run repeatedly:
    ldr = analogRead(A0);
    y = 0;
    if(ldr < 500){
        Serial.println("Goodevening!");
        streetlightsActivated();
        analogWrite(light1, 4);
        analogWrite(light2, 4);
        analogWrite(light3, 4);
        while(y == 0){
          ldr = analogRead(A0);
          
          if(ldr > 500){
              Serial.println("Goodmorning!");
              streetlightsDeactivated();
              y++;
            }
          ping1();
          if((distance1 < 0.10) && (distance1 >= 0.03)){
              z = 0;
              ping1Detected();
            }
          ping2();
          if((distance2 < 0.10) && (distance2 >= 0.03)){
              r = 0;
              ping2Detected();
            }
          ping3();
          if((distance3 < 0.10) && (distance3 >= 0.03)){
              s = 0;
              ping3Detected();
            }
          if((millis() - previousTime1) > ledInterval){
              analogWrite(light1, 4);
            }
          if((millis() - previousTime2) > ledInterval){
              analogWrite(light2, 4);
            }
          if((millis() - previousTime3) > ledInterval){
              analogWrite(light3, 4);
            }
        }
       }
       else{
          analogWrite(light1, 0);
          analogWrite(light2, 0);
          analogWrite(light3, 0);
        }
      
}
