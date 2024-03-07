#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

#define MAXBUF_REQUIREMENT 48
#define SEN5X_I2C_ADDRESS 0x69

int filestorage(){
  char filename[25];
  sprintf(filename, "Datalogg_%lu.txt", millis());
  File dataFile = SD.open(filename, FILE_WRITE);
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
      return 1;
    }
  }