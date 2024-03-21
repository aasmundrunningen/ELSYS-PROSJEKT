#include <SensirionI2CSen5x.h>
#include <Arduino.h>
#include <Wire.h>

SensirionI2CSen5x sen5x;

struct Measurment_data{
  float mcPm1p0;
  float mcPm2p5;
  float mcPm4p0;
  float mcPm10p0;
  float ambientHumidity;
  float ambientTemperature;
  float vocIndex;
  float noxIndex;
};
Measurment_data measurment_data = {
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

void get_measurment(){
uint16_t error;
  

  delay(3000);

  error = sen5x.readMeasuredValues(measurment_data.mcPm1p0, measurment_data.mcPm2p5, measurment_data.mcPm4p0, measurment_data.mcPm10p0, measurment_data.ambientHumidity, measurment_data.ambientTemperature, 
    measurment_data.vocIndex, measurment_data.noxIndex);

  if (error) {
    Serial.print("Error trying to execute readMeasuredValues(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } else {
    Serial.print("Mass Concentration Pm1p0: ");
    Serial.println(measurment_data.mcPm1p0);
    Serial.print("Mass Concentration Pm2p5: ");
    Serial.println(measurment_data.mcPm2p5);
    Serial.print("Mass Concentration Pm4p0: ");
    Serial.println(measurment_data.mcPm4p0);
    Serial.print("Mass Concentration Pm10p0: ");
    Serial.println(measurment_data.mcPm10p0);
}
}