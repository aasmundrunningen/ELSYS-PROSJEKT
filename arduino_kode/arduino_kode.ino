#include "ArduinoLowPower.h"
#include "Low_power.hpp"
#include "State_machine.hpp"
#include "Config.h"
#include "Utilities.hpp"
#include "measurment.hpp"

void setup(){
  led_init();
  digitalWrite(GREEN_LED, HIGH);
  Serial.begin(115200);
  
  measure_init();
  if(Serial){Serial.println("Starting program");}
  pinMode(USB_DETECT, INPUT);
  pinMode(MEASURE_MODE_SWITCH, INPUT_PULLUP);
  pinMode(BATTERY_INDICATOR_BUTTON, INPUT_PULLUP);
  set_state(DEEP_SLEEP);
  delay(5000);
}

void loop(){
  run_state_machine();
}


