#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
const int trigPin1 = D1;
const int echoPin1 = D2;
#define yelled D3 
#define grnled D4
#define BUZZER D5 //buzzer pin
#define float_switch D6 
unsigned long ch_no = 2635824;//Replace with Thingspeak Channel number
const char * write_api = "0OUAQV0GC6K9S3NS";//Replace with Thingspeak write API
char auth[] = "mwa0000018819725";
char ssid[] = "Mikko";
char pass[] = "00CartesianManipulator#";
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 10000;
WiFiClient  client;
long duration1;
int distance1;
void setup()
{
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(yelled, OUTPUT);
  pinMode(grnled, OUTPUT);
  pinMode(float_switch, INPUT_PULLUP);
  digitalWrite(yelled, LOW);
  digitalWrite(grnled, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
  startMillis = millis();  //initial start time
}
void loop()
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  Serial.println(distance1);

 if ((distance1 <= 4) || (digitalRead(float_switch) == HIGH))
//if ((distance1 <= 4) == HIGH)
  {
    digitalWrite(yelled, HIGH);
    tone(BUZZER, 300);
    digitalWrite(grnled, LOW);
    //delay(1500);
    
  }
  else
  {
    digitalWrite(grnled, HIGH);
    digitalWrite(yelled, LOW);
    delay(1500);
    noTone(BUZZER);
  }
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
  {
    ThingSpeak.setField(1, distance1);
    ThingSpeak.writeFields(ch_no, write_api);
    startMillis = currentMillis;
  }
}
