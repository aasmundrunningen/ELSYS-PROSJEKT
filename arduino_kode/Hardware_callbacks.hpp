
struct Callback_flags;

void measure_battery_callback();
void measure_callback();
void usb_detect_callback();
Callback_flags get_callback_flags();
void reset_callback_flags();

struct Callback_flags{
    bool measure_battery;
    bool measure;
    bool usb_detected;
};