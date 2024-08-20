#include <SoftwareSerial.h>
SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number = "+639770798025";

void setup() {
  // put your setup code here, to run once:
//delay(7000);
Serial.begin(9600);
_buffer.reserve(50);
Serial.println("System Started...");
sim.begin(9600);
delay(1000);
Serial.println("Type s to send an SMS, r to receive an SMS, and c to make a call.")
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0)
  switch (Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      ReceiveMessage();
      break;
    case 'c';
      callNumber();
      break;
  }
if (sim.available() > 0)
  Serial.write(sim.read());
  {
    void SendMessage()
  }
  sim
}
