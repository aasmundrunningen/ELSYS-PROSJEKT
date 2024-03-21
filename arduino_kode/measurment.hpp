
struct Measurment_data{
  float mcPm1p0;
  float mcPm2p5;
  float mcPm4p0;
  float mcPm10p0;
  float ambientHumidity;
  float ambientTemperature;
  float vocIndex;
  float noxIndex;
};

void measure_init();
void start_measurment();
void stop_measurment();
void update_measurment();
Measurment_data get_measurment();