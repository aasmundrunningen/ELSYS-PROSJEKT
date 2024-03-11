#include "ArduinoLowPower.h"

#define BATTERY_INDICATOR_BUTTON 3
#define MEASURE_MODE_SWITCH 4
#define USB_DETECT 1
#define GREEN_LED 8
#define YELLOW_LED 7
#define RED_LED 6


#define measure_switch 9

enum State{
  INIT,
  MEASURE,
  BATTERY_MEASURE,
  CHARGING,
  DEEP_SLEEP
};

enum State state = INIT;

void setup(){
  led_init();
  digitalWrite(GREEN_LED, HIGH);
  while(!Serial){
    Serial.begin(9600);
  }
  
  Serial.println("Starting program");
  pinMode(USB_DETECT, INPUT);
  pinMode(MEASURE_MODE_SWITCH, INPUT_PULLUP);
  pinMode(BATTERY_INDICATOR_BUTTON, INPUT_PULLUP);
}

void loop(){
  digitalWrite(GREEN_LED, HIGH);
  delay(5000);
  digitalWrite(GREEN_LED, LOW);
  turn_on_low_power();
}


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

void turn_on_low_power(){
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  Serial.begin(9600);
  if(Serial){
    Serial.println("Going into deep sleep in 2s");
  }
  delay(2000);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  //LowPower.attachInterruptWakeup(BATTERY_INDICATOR_BUTTON, measure_battery_callback, FALLING);
  LowPower.attachInterruptWakeup(MEASURE_MODE_SWITCH, measure_callback, FALLING);
  LowPower.deepSleep();
}

void measure_battery_callback(){
  state = BATTERY_MEASURE
  
}

void measure_callback(){
  state = MEASURE;
}