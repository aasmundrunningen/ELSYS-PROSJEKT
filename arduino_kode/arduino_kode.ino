#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

#define MAXBUF_REQUIREMENT 48
#define SEN5X_I2C_ADDRESS 0x69

#define SERIAL_ENABLED

const char BASE_FILENAME = "Datafile_"
char filename[];
SensirionI2CSen5x sen5x;

const int chipSelect = SDCARD_SS_PIN; // Assuming you are using pin 10 for SD chip select

void serial_init(){
  #ifdef SERIAL_ENABLED
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("Starting setup...");
  #endif
}

void serial_print(*char[] _string){
  #ifdef SERIAL_ENABLED
  Serial.print(*_string);
  #endif
}

bool filesystem_init(){
    if (!SD.begin(chipSelect)) {
      serial_print("Card failed, or not present");
      while (1);
  }
  Serial.println("Card initialized.");

  int index = 0;
    while(SD.exists("%c%i", BASE_FILENAME, index)){
      index ++;
    }
  filename = "%c%i .csv", BASE_FILENAME, index;
  File dataFile = SD.open(filename, FILE_WRITE);
  dataFile.println("time (ms), 1um, 2.5um, 4mu, 10mu");
  dataFile.close();
}

void filesystem_log_data(float _mcPm1p0, float _mcPm2p5, float _mcPm4p0, float _mcPm10p0){
    File dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile) {
      // Write data to the file in CSV format
      dataFile.print(millis());
      dataFile.print(",");
      dataFile.print(_mcPm1p0);
      dataFile.print(",");
      dataFile.print(_mcPm2p5);
      dataFile.print(",");
      dataFile.print(_mcPm4p0);
      dataFile.print(",");
      dataFile.println(_mcPm10p0);
      dataFile.close();
      Serial.println("Data written to datalog.csv.");
    } else {
      Serial.println("Error opening datalog.csv");
    }
}


void setup() {
  serial_init();

  Wire.begin();
  sen5x.begin(Wire);

  filesystem_init();

  uint16_t error;
  char errorMessage[256];
  error = sen5x.deviceReset();
  if (error) {
    Serial.print("Error trying to execute deviceReset(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }

  Serial.println("Starting measurement...");
  error = sen5x.startMeasurement();
  if (error) {
    Serial.print("Error trying to execute startMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }

  Serial.println("Setup complete.");
}

void loop() {
  uint16_t error;
  char errorMessage[256];

  delay(3000);

  float mcPm1p0;
  float mcPm2p5;
  float mcPm4p0;
  float mcPm10p0;
  float ambientHumidity;
  float ambientTemperature;
  float vocIndex;
  float noxIndex;

  error = sen5x.readMeasuredValues(mcPm1p0, mcPm2p5, mcPm4p0, mcPm10p0, ambientHumidity, ambientTemperature, 
    vocIndex, noxIndex);

  if (error) {
    Serial.print("Error trying to execute readMeasuredValues(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } else {
    Serial.print("Mass Concentration Pm1p0: ");
    Serial.println(mcPm1p0);
    Serial.print("Mass Concentration Pm2p5: ");
    Serial.println(mcPm2p5);
    Serial.print("Mass Concentration Pm4p0: ");
    Serial.println(mcPm4p0);
    Serial.print("Mass Concentration Pm10p0: ");
    Serial.println(mcPm10p0);

    // Open the file for writing
    filesystem_log_data(mcPm1p0, mcPm2p5, mcPm4p0, mcPm10p0);
  }
}