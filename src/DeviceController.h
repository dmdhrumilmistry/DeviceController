#ifndef DEVICECONTROLLER_H_
#define DEVICECONTROLLER_H_

#include "Arduino.h"
#include "string.h"

class DeviceController
{
private:
    int min_pin_num;
    int max_pin_num;

public:
    DeviceController(int min_pins, int max_pins);
    void set_pin_state(int pin_type, int pin, int state);
    void set_values(char *message);
};

#endif