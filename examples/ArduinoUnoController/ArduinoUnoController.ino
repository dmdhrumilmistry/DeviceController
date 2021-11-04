#include <DeviceController.h>

DeviceController arduino(0,13); //min_pin_number, max_pin_number

String message;
char msg[36]; // bufflen = 7n + 1 : for n = 5, bufflen = 36
int Heater = 5;
int LED = 9;
int TV = 10;
int AC = 13;


void setup(){
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(TV, OUTPUT);
    pinMode(AC, OUTPUT);
    pinMode(Heater, OUTPUT);
}

void loop()
{
    while (!Serial.available());
    message = Serial.readString();
    message.toCharArray(msg, 36); // Change bufflen value here
    arduino.set_values(msg);
}