#include <SensirionI2CSen5x.h>
#include <Arduino.h>
#include <Wire.h>
#include "measurment.hpp"

SensirionI2CSen5x sen5x;


struct Measurment_data measurment_data = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

char errorMessage[256];



void measure_init(){
  Wire.begin();
  sen5x.begin(Wire);
}

void start_measurment(){
  sen5x.startMeasurement();
}

void stop_measurment(){
  sen5x.stopMeasurement();
}

void update_measurment(){
  uint16_t error;
  error = sen5x.readMeasuredValues(measurment_data.mcPm1p0, measurment_data.mcPm2p5, measurment_data.mcPm4p0, measurment_data.mcPm10p0, measurment_data.ambientHumidity, measurment_data.ambientTemperature, 
  measurment_data.vocIndex, measurment_data.noxIndex);
}

Measurment_data get_measurment(){
  return measurment_data;
}