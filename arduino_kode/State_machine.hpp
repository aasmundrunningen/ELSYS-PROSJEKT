

enum State{
  INIT,
  MEASURE,
  BATTERY_MEASURE,
  CHARGING,
  DEEP_SLEEP
};

void run_state_machine();
void set_state(State _state);