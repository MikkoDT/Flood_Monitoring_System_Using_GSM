#include <SoftwareSerial.h>

SoftwareSerial sim800l(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    if (input == "sms") {
      sendSMS();
    }
  }
}

void sendSMS() {
  sim800l.println("AT+CMGF=1"); // Set SMS mode to text
  delay(100);
  sim800l.println("AT+CMGS=\"+639568517289\""); // Replace with the number you want to send the SMS to
  delay(100);
  sim800l.print("Hello, this is a test message."); // Replace with the message you want to send
  delay(100);
  sim800l.write(26); // End the message by sending the ASCII code of Ctrl+Z
  delay(100);
}