#include "DigitalDevice.h"

#include "Arduino.h"

DigitalDevice::DigitalDevice(int pin, int mode, String name) {
    pinMode(pin, mode);
    this->pin = pin;
    this->mode = mode;
    this->name = name;
}

DigitalDevice DigitalDevice::input(int pin, String name) {
    return DigitalDevice(pin, INPUT, name);
}

DigitalDevice DigitalDevice::output(int pin, String name) {
    return DigitalDevice(pin, OUTPUT, name);
}

int DigitalDevice::get() {
    return digitalRead(pin);
}

void DigitalDevice::set(int value) {
   // Serial.print("********** Set ");
   // Serial.print(name);
   // Serial.print(": ");
   // Serial.println(value);

    digitalWrite(pin, value);
}

int DigitalDevice::getPin() {
    return pin;
}

int DigitalDevice::getMode() {
    return mode;
}

String DigitalDevice::getName() {
    return name;
}
