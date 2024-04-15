#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include "measurment.hpp"
#include "fillagring.hpp"

#define MAXBUF_REQUIREMENT 48
#define SEN5X_I2C_ADDRESS 0x69

const int chipSelect = SDCARD_SS_PIN;

char filename[25];


void init_file(){
    if(!SD.begin(chipSelect)){
        if(Serial){Serial.println("Error: SD-card not detected");}
    }else{
        int counter = 0;
        sprintf(filename, "D%i.csv",counter);
        while(SD.exists(filename)){
            counter++;
            sprintf(filename, "D%i.csv",counter);
        }
        if(Serial){Serial.println(filename);}
    }
    
}
struct Measurment_data data;
File dataFile;
int store_data(){
    data = get_measurment();
    dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile) {
      // Write data to the file in CSV format
      dataFile.print(data.mcPm1p0);
      dataFile.print(",");
      dataFile.print(data.mcPm2p5);
      dataFile.print(",");
      dataFile.print(data.mcPm4p0);
      dataFile.print(",");
      dataFile.println(data.mcPm10p0);
      dataFile.close();
      return 1;
    }
}