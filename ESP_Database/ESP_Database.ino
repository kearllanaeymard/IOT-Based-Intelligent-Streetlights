#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "ELLAMARIANO";
const char *password = "ella021872";
const char *host = "http://000webhostapp.com";

char inputData;
boolean newData = false;

void receiveInput(){
    if(Serial.available()){
        inputData = Serial.read();
        newData = true;
      }
  }

void showInput(){
    if(newData == true){
        Serial.println(inputData);
        newData = false;
      }
  }

void insertStationData(String station){
    HTTPClient http;
    String getData, Link;
    getData = "?station=" + station;
    Link = "http://pupiotdevelopment.000webhostapp.com/getstation.php" + getData;
    http.begin(Link);
    int httpCode = http.GET();
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
    http.end();
  }

void insertActivationData(String lightStatus){
    HTTPClient http;
    String getData, Link;
    getData = "?streetlights=" + lightStatus;
    Link = "http://pupiotdevelopment.000webhostapp.com/getactivation.php" + getData;
    http.begin(Link);
    int httpCode = http.GET();
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
    http.end();
  }

void setup() {
  delay(1000);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);        
  delay(1000);
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(2, HIGH);
  delay(200);
  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  Serial.write('X');
}

void loop() {
  receiveInput();
  showInput();
  if(inputData == 'A'){
    insertStationData("StationA");
    inputData = 'o';
  }
  else if(inputData == 'B'){
    insertStationData("StationB");
    inputData = 'o';
  }
  else if(inputData == 'C'){
    insertStationData("StationC");
    inputData = 'o';
  }
  else if(inputData == 'N'){
      insertActivationData("Activated");
    }
  else if(inputData == 'F'){
      insertActivationData("Deactivated");
}
}
