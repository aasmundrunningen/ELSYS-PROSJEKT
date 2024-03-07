#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <time.h>

#define MAXBUF_REQUIREMENT 48
#define SEN5X_I2C_ADDRESS 0x69

SensirionI2CSen5x sen5x;

const int chipSelect = SDCARD_SS_PIN; // Assuming you are using pin 10 for SD chip select

void setup() {

  Wire.begin();
  sen5x.begin(Wire);

  uint16_t error;
  char errorMessage[256];
  sen5x.deviceReset();
 
  sen5x.startMeasurement();
  
}

int time(){
   // Få gjeldende tid
   time_t now = time(NULL);
   struct tm *t = localtime(&now);
}

void loop() {
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

  sen5x.readMeasuredValues(mcPm1p0, mcPm2p5, mcPm4p0, mcPm10p0, ambientHumidity, ambientTemperature, 
    vocIndex, noxIndex);


    // Open the file for writing
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(filename, sizeof(filename), "File_%Y-%m-%d_%H-%M-%S.txt", t);
    File dataFile = SD.open("datalog_%Y-%m-%d-%H-%M.csv", FILE_WRITE);
    if (dataFile) {
      // Write data to the file in CSV format
      dataFile.print(mcPm1p0);
      dataFile.print(",");
      dataFile.print(mcPm2p5);
      dataFile.print(",");
      dataFile.print(mcPm4p0);
      dataFile.print(",");
      dataFile.println(mcPm10p0);
      dataFile.close();
      
    }
  }