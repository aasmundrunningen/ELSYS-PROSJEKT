#include "State_machine.hpp"
#include "Low_power.hpp"
#include "Config.h"
#include "Utilities.hpp"
#include "Arduino.h"

enum State state = INIT;

void set_state(State _state){
    state = _state;
}

void run_state_machine(){
  if(state == BATTERY_MEASURE){
    return;
  }else if(state == MEASURE){
    set_led_state(1,1,0);
    if(digitalRead(MEASURE_MODE_SWITCH) == 1){
        set_led_state(0,1,1);
        delay(1000);
        state = DEEP_SLEEP;
    }
  }else if(state == CHARGING){
    return;
  }else if(state == DEEP_SLEEP){
    turn_on_low_power();
  } 
}