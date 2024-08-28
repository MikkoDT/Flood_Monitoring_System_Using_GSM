#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the address (0x27) if necessary

const int trigPin1 = D1;
const int echoPin1 = D2;
#define redled D3
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
  pinMode(redled, OUTPUT);
  pinMode(grnled, OUTPUT);
  pinMode(float_switch, INPUT_PULLUP);
  digitalWrite(redled, LOW);
  digitalWrite(grnled, LOW);
  Serial.begin(115200);

  // Initialize LCD
  lcd.begin();
  lcd.backlight();

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
  {
    digitalWrite(redled, HIGH);
    tone(BUZZER, 300);
    digitalWrite(grnled, LOW);
    //delay(1500);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Flood Detected");
    lcd.setCursor(0, 1);
    lcd.print("Dist: ");
    lcd.print(distance1);
    lcd.print(" cm");
  }
  else
  {
    digitalWrite(grnled, HIGH);
    digitalWrite(redled, LOW);
    delay(1500);
    noTone(BUZZER);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Flood Detected");
    lcd.setCursor(0, 1);
    lcd.print("Dist: ");
    lcd.print(distance1);
    lcd.print(" cm");
  }
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
  {
    ThingSpeak.setField(1, distance1);
    ThingSpeak.writeFields(ch_no, write_api);
    startMillis = currentMillis;
  }
}