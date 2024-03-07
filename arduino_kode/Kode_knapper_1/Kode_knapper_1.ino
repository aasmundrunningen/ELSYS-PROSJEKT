
const int buttonPin1 = 2;  // the number of the pushbutton pin 1
const int buttonPin2 = 3;  // the number of the pushbutton pin 2
const int ledPin1 = 10;    // the number of the LED pin 1
const int ledPin2 = 11;    // the number of the LED pin 2
const int ledPin3 = 12;    // the number of the LED pin 3


int buttonState1 = 0;  // variable for reading the pushbutton status 1
int buttonState2 = 0;  // variable for reading the pushbutton status 2
int spenning = 0; // variable to store measurement

void setup() {
  // initialize the LED pins as outputs:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  // initialize the pushbutton pins as inputs:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop() {
  // read the state of the pushbutton values:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  
  // check if the pushbutton 1 is pressed. If it is, the buttonState1 is HIGH:
  if (buttonState1 == HIGH) {
    // start measurement
    
    // if buttonstate 2 is HIGH then execute this code:
    if (buttonState2 == HIGH) {
      // Code to measure voltage and set LEDs based on voltage range
      // Assuming 'spenning' holds the voltage measurement
      if (spenning >= 0 && spenning < 200)
        digitalWrite(ledPin1, HIGH);
      else if (spenning >= 200 && spenning < 400)
        digitalWrite(ledPin2, HIGH);
      else if (spenning >= 400 && spenning < 600)
        digitalWrite(ledPin3, HIGH);
    }
  } else {
    // stop measurement
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }
}

