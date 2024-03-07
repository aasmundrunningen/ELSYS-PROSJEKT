#include "ArduinoLowPower.h"

#define battery_indicator A1
#define battery_inidcator_switch 3

#define measure_switch 9

void begin(){
  LowPower.attachInterruptWakeup(pin, callback, mode)

}

void loop(){

}


void turn_on_low_power(){
  LowPower.attachInterruptWakeup(battery_indicator_switch, measure_battery_callback, FALLING);
  LowPower.attachInterruptWakeup(measure_switch, measure_callback, FALLING);
  LowPower.deepSleep();
}

void measure_battery_init(){
  pinMode(battery_indicator, INPUT);
  pinMode(battery_indicator_switch, INPUT_PULLUP);
}



void measure_battery_callback(){

}

void measure_callback(){

}