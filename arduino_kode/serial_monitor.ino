#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

#define MAXBUF_REQUIREMENT 48
#define SEN5X_I2C_ADDRESS 0x69

    //i loopen må det være en if  setning som sjekker om pin x er høy.

int debug(){
    //setup
    Serial.begin(115200);
    while (!Serial) {
       delay(100);
    }
    Serial.println("Starting setup...");

    Wire.begin();
    sen5x.begin(Wire);

    Serial.print("Initializing SD card...");
    if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
        while (1);
    }
    Serial.println("Card initialized.");

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

    //batteri
    float voltage = measure_battery_voltage();
    float maxVoltage = 4.2; 
    float minVoltage = 3.0; 
    if (voltage > maxVoltage) voltage = maxVoltage;
    if (voltage < minVoltage) voltage = minVoltage;
    float percentage = (voltage - minVoltage) / (maxVoltage - minVoltage) * 100;
    Serial.printf("Battery percentage: %.2f%%\n", percentage);


    //Målinger
    uint16_t error;
    char errorMessage[256];

    delay(3000);

    error = sen5x.readMeasuredValues(mcPm1p0, mcPm2p5, mcPm4p0, mcPm10p0, ambientHumidity, ambientTemperature, 
    vocIndex, noxIndex);

    if (error) {
        Serial.print("Error trying to execute readMeasuredValues(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } 
    else {
        Serial.print("Mass Concentration Pm1p0: ");
        Serial.println(mcPm1p0);
        Serial.print("Mass Concentration Pm2p5: ");
        Serial.println(mcPm2p5);
        Serial.print("Mass Concentration Pm4p0: ");
        Serial.println(mcPm4p0);
        Serial.print("Mass Concentration Pm10p0: ");
        Serial.println(mcPm10p0);
    }
}    



