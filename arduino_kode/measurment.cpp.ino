


void gjor_maling(){
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
}