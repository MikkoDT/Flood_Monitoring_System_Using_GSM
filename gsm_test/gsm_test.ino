#include <SoftwareSerial.h>

SoftwareSerial sim(2, 3);

String phoneNumber = "+639568517289"; // change to your number

void setup() {
  Serial.begin(9600);
  sim.begin(9600);
  delay(1000);
  Serial.println("Type s to send an SMS, r to receive an SMS, and c to make a call");
}

void loop() {
  if (Serial.available() > 0) {
    switch (Serial.read()) {
      case 's':
        sendSMS();
        break;
      case 'r':
        receiveSMS();
        break;
      case 'c':
        callNumber();
        break;
    }
  }

  if (sim.available() > 0) {
    Serial.write(sim.read());
  }
}

void sendSMS() {
  sim.println("AT+CMGF=1"); // Set message format to text mode
  delay(1000);
  if(sim.find("OK")) {
    Serial.println("Set SMS text mode successfully.");
  } else {
    Serial.println("Failed to set SMS text mode.");
    return;
  }
  
  sim.println("AT+CMGS=\"" + phoneNumber + "\""); // Set recipient phone number
  delay(1000);
  if(sim.find(">")) {
    sim.print("Hello, how are you? Greetings from ChatGPT!"); // Set SMS content
    delay(100);
    sim.write(26); // Send Ctrl+Z character to end message
    delay(3000); // Wait for message to be sent (can take a while)
    if(sim.find("OK")) {
      Serial.println("SMS sent successfully!");
    } else {
      Serial.println("Failed to send SMS.");
    }
  } else {
    Serial.println("Failed to get prompt to send SMS.");
  }
}

void receiveSMS() {
  sim.println("AT+CMGF=1"); // Set message format to text mode
  delay(1000);
  if(sim.find("OK")) {
    Serial.println("Set SMS text mode successfully.");
  } else {
    Serial.println("Failed to set SMS text mode.");
    return;
  }
  
  sim.println("AT+CNMI=1,2,0,0,0"); // Enable new message notifications
  delay(1000);
  if(sim.find("OK")) {
    Serial.println("Listening for new messages...");
  } else {
    Serial.println("Failed to set SMS notification mode.");
  }
}

void callNumber() {
  sim.println("ATD" + phoneNumber + ";"); // Make the call
  delay(10000); // Wait for call to be established
  sim.println("ATH"); // Hang up
  Serial.println("Call ended!");
}