#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

#define redled D3
#define grnled D4
#define BUZZER D5 //buzzer pin

unsigned long ch_no = 1053193;//Replace with Thingspeak Channel number
const char * write_api = "1WGTOHK9622G57JI";//Replace with Thingspeak write API
char auth[] = "mwa0000018384149";
char ssid[] = "Alsan Air WiFi 4";
char pass[] = "11122235122@kap1";

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 10000;
WiFiClient  client;
long duration1;
int distance1;

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

    digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

    if (distance1 <= 4)
  {
    digitalWrite(D3, HIGH);
    tone(BUZZER, 300);
    digitalWrite(D4, LOW);
    delay(1500);
    noTone(BUZZER);
  }
  else
  {
    digitalWrite(D4, HIGH);
    digitalWrite(D3, LOW);
  }

  if (currentMillis - startMillis >= period)
  {
    ThingSpeak.setField(1, distance1);
    ThingSpeak.writeFields(ch_no, write_api);
    startMillis = currentMillis;
  }

  