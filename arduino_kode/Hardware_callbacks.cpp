#include "State_machine.hpp"
#include "Hardware_callbacks.hpp"
#include "Arduino.h"


Callback_flags callback_flags;

void reset_callback_flags(){
    callback_flags = {0,0,0};
}


void measure_battery_callback(){
  callback_flags.measure_battery = 1;
  Serial.println("measyre battery callback");
}

void measure_callback(){
  callback_flags.measure = 1;
}

void usb_detect_callback(){
    callback_flags.usb_detected = 1;
}