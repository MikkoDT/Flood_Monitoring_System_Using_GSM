//Set the LED light to pin 8
12345678910111213
//Set the LED light to pin 8
int LED = 8;

12345678910111213
//Set the LED light to pin 8
int LED = 8;

//Set the float sensor to pin 3
#define Float_Switch 3



int LED = 8;

12345678910111213
//Set the LED light to pin 8
int LED = 8;

//Set the float sensor to pin 3
#define Float_Switch 3

void setup() {

  // initialize digital pin 8 as an output.
  pinMode(LED, OUTPUT);


//Set the float sensor to pin 3
#define Float_Switch 3

void setup() {

  // initialize digital pin 8 as an output.
  pinMode(LED, OUTPUT);

 
  pinMode(Float_Switch, INPUT_PULLUP);
}

void loop() {
 
 if(digitalRead(Float_Switch) == HIGH)
  {
    digitalWrite(LED, HIGH); //Turn LED on
  }

 else
  {
    digitalWrite(LED, LOW); //Turn LED off
  }
}
