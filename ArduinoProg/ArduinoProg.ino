#include<SoftwareSerial.h>
SoftwareSerial mySerial(11, 3);

int ldr = analogRead(A0);
int light1 = 5;
int light2 = 6;
int light3 = 7;

char inputData;
boolean newData = false;
int x = 0;
int y;
int btn1, btn2, btn3;

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

void btn1Pressed(){
    btn1 = digitalRead(8);
    while(btn1 == 1){
        btn1 = digitalRead(8);
        if(btn1 == 0){
        mySerial.write('A');
        mySerial.write("o");
      }
      }
    Serial.println("Data Recorded Successfully Light A");
  }

void btn2Pressed(){
    btn2 = digitalRead(9);
    while(btn2 == 1){
        btn2 = digitalRead(9);
        if(btn2 == 0){
        mySerial.write('B');
        mySerial.write("o");
      }
      }
    Serial.println("Data Recorded Successfully Light B");  
  }

void btn3Pressed(){
    btn3 = digitalRead(10);
    while(btn3 == 1){
        btn3 = digitalRead(10);
        if(btn3 == 0){
        mySerial.write('C');
        mySerial.write("o");
      }
      }
    Serial.println("Data Recorded Successfully Light C");
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
}


void loop() {
  // put your main code here, to run repeatedly:
    ldr = analogRead(A0);
    y = 0;
    if(ldr < 500){
        Serial.println("Goodevening!");
        streetlightsActivated();
        while(y == 0){
          ldr = analogRead(A0);
          if(ldr > 500){
              Serial.println("Goodmorning!");
              streetlightsDeactivated();
              y++;
            }
          btn1 = digitalRead(8);
          btn2 = digitalRead(9);
          btn3 = digitalRead(10);
          analogWrite(light1, 4);
          analogWrite(light2, 4);
          analogWrite(light3, 4);
      
          if(btn1 == 1){
              btn1Pressed();
              Serial.println("Recorded A");
              analogWrite(light1, 255);
              delay(3000);
            }
          if(btn2 == 1){
              btn2Pressed();
              Serial.println("Recorded B");
              analogWrite(light2, 255);
              delay(3000);
            }
          if(btn3 == 1){
              btn3Pressed();
              Serial.println("Recorded C");
              analogWrite(light3, 255);
              delay(3000);
            }
        }
       }
       else{
          analogWrite(light1, 0);
          analogWrite(light2, 0);
          analogWrite(light3, 0);
        }
      
}
