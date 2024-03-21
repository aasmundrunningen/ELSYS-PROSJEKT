

enum State{
  INIT,
  MEASURE,
  BATTERY_MEASURE,
  CHARGING,
  INIT_MEASURMENT,
  DEEP_SLEEP
};


void run_state_machine();
void set_state(State _state);