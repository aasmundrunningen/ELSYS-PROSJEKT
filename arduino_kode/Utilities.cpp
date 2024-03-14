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