void led_init();
void set_led_state(bool _greeen, bool _yellow, bool _red);
bool charging();
void toogle_green_led(int periode);
void toogle_battery_led(int periode);
float measure_battery_voltage();
void display_battery_voltage();