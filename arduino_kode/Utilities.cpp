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


bool battery_led_state = 0;
int _battery_time = 0;
void toogle_battery_led(int periode){
  if(_battery_time + periode < millis()){
    _battery_time = millis();
    battery_led_state = !battery_led_state;
  }
  if(battery_led_state){
    display_battery_voltage();
  }else{
    set_led_state(0,0,0);
  }
}


bool charging(){
    return digitalRead(USB_DETECT);
}

float measure_battery_voltage(){
  int sensorValue = analogRead(ADC_BATTERY);
  float voltage = sensorValue * (3.3 / 1023.0) *(1.2+0.33) / 1.2;
  //sensorValue blir måler 0-3.3V som en 0-1023 verdi og batterispenningen går gjennom en spenningsdeler med 1.2MOhm og 330KOhm
  if (voltage > MAX_VOLTAGE){ voltage = MAX_VOLTAGE;}
  if (voltage < MIN_VOLTAGE){ voltage = MIN_VOLTAGE;}
  float percentage = (voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE) * 100;
  return percentage;

}

void display_battery_voltage(){
  float voltage = measure_battery_voltage();
  if(voltage < BATTERY_PERCENTAGE_RED){
    set_led_state(0,0,1);
  }else if(voltage < BATTERY_PERCENTAGE_GREEN){
    set_led_state(0,1,0);
  }else{
    set_led_state(1,0,0);
  }
}