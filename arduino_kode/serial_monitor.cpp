#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include "measurment.hpp"
#include "Utilities.hpp"

#define MAXBUF_REQUIREMENT 48
#define SEN5X_I2C_ADDRESS 0x69

    //i loopen må det være en if  setning som sjekker om pin x er høy.

void debug(){
    //setup
    Serial.begin(115200);
    if(!Serial) {
       return;
    }

    //batteri
    float percentage = measure_battery_voltage();
    Serial.print("Battery percentage: ");
    Serial.println(percentage);
}



void seriel_maalinger(Measurment_data data){
    Serial.begin(115200);
    if(!Serial) {
       return;
    }
    uint16_t error;
    char errorMessage[256];
    //Målinger ved målemodus
    if (error) {
        Serial.print("Error trying to execute readMeasuredValues(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }
    else {
        Serial.print("Mass Concentration Pm1p0: ");
        Serial.println(data.mcPm1p0);
        Serial.print("Mass Concentration Pm2p5: ");
        Serial.println(data.mcPm2p5);
        Serial.print("Mass Concentration Pm4p0: ");
        Serial.println(data.mcPm4p0);
        Serial.print("Mass Concentration Pm10p0: ");
        Serial.println(data.mcPm10p0);
    }
}



