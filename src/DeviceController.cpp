#include "DeviceController.h"
#include "Arduino.h"
#include "string.h"

/*  packet encapsulation method
    message : 0:9:1,1:10:0,0:13:1,0:5:0,
    command : 0:9:1
    pin_type : 0 (0->Digital, 1->Analog)
    pin_num : 9
    pin_state : 1 (0->OFF, 1->ON)

    Test message : 0:9:1,0:10:0,0:13:1,0:5:0,
    Test message : 0:9:1,0:10:1,0:13:0,0:5:0,
    Test message : 0:9:0,0:10:1,0:13:1,0:5:0,
    Test message : 0:9:0,0:10:0,0:13:0,0:5:1,

    0 : 9 : 1,
    space -> for
    1n-> pin_type
    2n-> pin_num
    1n -> pin_state
    2n -> :
    1n -> ,
    1 -> \0 (str_end)
    7n + 1 -> Worst Case Total Bufflen
    7(5) + 1 = 36 -> Bufflen
*/

DeviceController::DeviceController(int min_pins, int max_pins)
{
    min_pin_num = min_pins;
    max_pin_num = max_pins;
}

/*
    function name : set_pin_state
    args: pin(int), state(int)
    returns : NULL
    description : set passed argument pin with its state
    */
void DeviceController::set_pin_state(int pin_type, int pin, int state)
{
    /* PinType        Type
     0              Digital
     1              Analog
  */
    if (pin_type == 0)
    {
        /* Check if pin and state are in range*/
        if (pin >= min_pin_num && pin <= max_pin_num && state >= 0 && state <= 1)
        {
            digitalWrite(pin, state);
        }
        else
        {
            digitalWrite(pin, 0);
        }
    }
    else
    {
        /* Check if pin and state are in range*/
        if (pin >= min_pin_num && pin <= max_pin_num && state >= 0 && state <= 1)
        {
            analogWrite(pin, state);
        }
        else
        {
            analogWrite(pin, 0);
        }
    }
}

/*
    function name : set_values
    args: string(char*)
    returns : NULL
    Serial Syntax : [Pin_num]:[state],[Pin_num]:state,...,
    description : stores pin number received from serial port to pin char* and state in value char*
    */
void DeviceController::set_values(char *string)
{
    // message(char*), pin(char*), value(char*)
    char *command = strchr(string, ',');

    while (command != NULL)
    {
        *command++ = '\0';
        char *data = strtok(string, ":");
        if (data != NULL)
        {
            int pin_type = atoi(data);

            data = strtok(NULL, ":");
            int pin_num = atoi(data);

            data = strtok(NULL, ":");
            int pin_state = atoi(data);

            this->set_pin_state(pin_type, pin_num, pin_state);
        }

        string = command;
        command = strchr(string, ',');
    }
}