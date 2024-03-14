#include "State_machine.hpp"


void measure_battery_callback(){
  set_state(BATTERY_MEASURE);
}

void measure_callback(){
  set_state(MEASURE); 
}

void usb_detect_callback(){
    set_state(CHARGING);
}