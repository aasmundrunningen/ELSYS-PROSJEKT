#include "State_machine.hpp"
#include "Low_power.hpp"
#include "Config.h"
#include "Utilities.hpp"
#include "Arduino.h"
#include "Hardware_callbacks.hpp"
#include <map>


const char * const State_to_string[] =
{
    [INIT] = "init",
    [MEASURE] = "measure",
    [BATTERY_MEASURE]  = "battery measure",
    [CHARGING]  = "charging",
    [INIT_MEASURMENT] = "init measurment",
    [DEEP_SLEEP] = "Deep sleep"
};


enum State state = INIT;
extern Callback_flags callback_flags;

void set_state(State _state){
    enum State old_state = state;
    state = _state;
    Serial.print(State_to_string[old_state]);
    Serial.print(" -> ");
    Serial.println(State_to_string[state]);
}

void run_state_machine(){
    switch(state){
        case INIT:
            if(charging()){
                set_state(CHARGING);
            }else{
                set_state(DEEP_SLEEP);
            }
            break;
        case CHARGING:
          set_led_state(1,0,0);
            if(!charging()){
                set_state(DEEP_SLEEP);
            }
            if(!digitalRead(MEASURE_MODE_SWITCH)){
                set_state(INIT_MEASURMENT);
            }
            break;
        case DEEP_SLEEP:
            if(!digitalRead(MEASURE_MODE_SWITCH)){
                set_state(INIT_MEASURMENT);
            }else if(charging()){
                set_state(CHARGING);
            }else if(callback_flags.measure_battery){
                set_state(BATTERY_MEASURE);
                reset_callback_flags();
            }else{
                turn_on_low_power();
            }
            break;
        case BATTERY_MEASURE:
            set_led_state(1,1,0);
            delay(5000);
            set_state(DEEP_SLEEP);
            break;
        case INIT_MEASURMENT:
            set_led_state(0,1,0);
            set_state(MEASURE);
            break;
        case MEASURE:
            toogle_green_led(1000);
            if(digitalRead(MEASURE_MODE_SWITCH)){
                if(charging()){
                    set_state(CHARGING);
                }else{
                    set_state(DEEP_SLEEP);
                }
            }
    }
}