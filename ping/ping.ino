  const  int trigger=30; 
  const  int echo=31;
  float  distance;
  
void setup(){
  Serial.begin(9600);
  pinMode(trigger,OUTPUT);
  pinMode(echo, INPUT);
}
void loop(){
  digitalWrite(trigger,LOW);
  delayMicroseconds(5);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  distance=pulseIn(echo,HIGH);
  distance=distance*0.0001657;
  Serial.println(distance);
}
