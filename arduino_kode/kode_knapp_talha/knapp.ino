#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

#define MAXBUF_REQUIREMENT 48
#define SEN5X_I2C_ADDRESS 0x69

SensirionI2CSen5x sen5x;

const int buttonPin1 = 2;  // the number of the pushbutton pin 1
const int buttonPin2 = 3;  // the number of the pushbutton pin 2
const int ledPin1 = 10;    // the number of the LED pin 1
const int ledPin2 = 11;    // the number of the LED pin 2
const int ledPin3 = 12;    // the number of the LED pin 3

int buttonState1 = 0;  // variable for reading the pushbutton status 1
int buttonState2 = 0;  // variable for reading the pushbutton status 2
int spenning = 0; // variable to store measurement

const int chipSelect = SDCARD_SS_PIN; // Assuming you are using pin 10 for SD chip select

void setup() {
  // initialize the LED pins as outputs:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  // initialize the pushbutton pins as inputs:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  // Start serial communication
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("Starting setup...");

  // Initialize sensor and SD card
  Wire.begin();
  sen5x.begin(Wire);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }

  // Reset sensor and start measurement
  uint16_t error = sen5x.deviceReset();
  if (error) {
    Serial.print("Error trying to execute deviceReset(): ");
    // Handle error
  }
  Serial.println("Starting measurement...");
  error = sen5x.startMeasurement();
  if (error) {
    Serial.print("Error trying to execute startMeasurement(): ");
    // Handle error
  }

  Serial.println("Setup complete.");
}

void loop() {
  // Read the state of the pushbutton values
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);


  // If button 2 is HIGH, set LEDs based on voltage range
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



  if (buttonState1 == HIGH) {
    // Start measurement
    Serial.println("Button 1 is pressed. Starting measurement...");
     // Read sensor values and write to SD card
    float mcPm1p0, mcPm2p5, mcPm4p0, mcPm10p0, ambientHumidity, ambientTemperature, vocIndex, noxIndex;
    uint16_t error = sen5x.readMeasuredValues(mcPm1p0, mcPm2p5, mcPm4p0, mcPm10p0, ambientHumidity, ambientTemperature, vocIndex, noxIndex);
    if (error) {
      Serial.print("Error trying to execute readMeasuredValues(): ");
      // Handle error
    } else {
      // Write data to SD card
      File dataFile = SD.open("datalog.csv", FILE_WRITE);
      if (dataFile) {
        dataFile.print(mcPm1p0);
        dataFile.print(",");
        dataFile.print(mcPm2p5);
        dataFile.print(",");
        dataFile.print(mcPm4p0);
        dataFile.print(",");
        dataFile.println(mcPm10p0);
        dataFile.close();
        Serial.println("Data written to datalog.csv.");

  } else {
    // Stop measurement and turn off LEDs
    Serial.println("Button 1 is not pressed. Stopping measurement...");
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    sen5x.stopMeasurement();
  }

  // Delay before next iteration
  delay(3000);
}