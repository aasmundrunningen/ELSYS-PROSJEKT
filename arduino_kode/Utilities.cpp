#include "Config.h"
#include "Arduino.h"

void led_init(){
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
  delay(5000);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void set_led_state(bool _green, bool _yellow, bool _red){
  digitalWrite(GREEN_LED, _green);
  digitalWrite(YELLOW_LED, _yellow);
  digitalWrite(RED_LED, _red);
}

bool green_led_state = 0;
int time = 0;
void toogle_green_led(int periode){
  if(time + periode < millis()){
    time = millis();
    green_led_state = !green_led_state;
  }
  digitalWrite(YELLOW_LED, 0);
  digitalWrite(RED_LED, 0);
  digitalWrite(GREEN_LED, green_led_state);
}

bool charging(){
    return digitalRead(USB_DETECT);
}