#include "Arduino.h"
#include "Config.h"
#include "ArduinoLowPower.h"
#include "Hardware_callbacks.hpp"
#include "Utilities.hpp"


void turn_on_low_power(){
  set_led_state(0, 1, 1);
  Serial.begin(9600);
  if(Serial){
    Serial.println("Going into deep sleep in 2s");
  }
  delay(2000);
  set_led_state(0,0,1);
  LowPower.attachInterruptWakeup(MEASURE_MODE_SWITCH, measure_callback, FALLING);
  LowPower.attachInterruptWakeup(BATTERY_INDICATOR_BUTTON, measure_battery_callback, FALLING);
  LowPower.attachInterruptWakeup(USB_DETECT, usb_detect_callback, RISING);
  LowPower.deepSleep();
}
