/*
  ButtonSet library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

#include "Arduino.h"
#include "ButtonSet.h"
#include "Debouncer.h"

#define DEFAULT_BOUNCE_TIME 100
#define DELTA 10


ButtonSet::ButtonSet(byte pin, int* values, int valuesSize) 
    : debouncer(DEFAULT_BOUNCE_TIME)
{
    this->pin = pin;
	this->values = values;
    this->valuesSize = valuesSize;
    
    pinMode(pin, INPUT);
}

ButtonSet ButtonSet::createWithValues(byte pin, int* values, int valuesSize) {
    return ButtonSet(pin, values, valuesSize);
}

ButtonSet ButtonSet::createWithResistors(byte pin, int power, int pullDown, int* pullUpValues, int pullUpValuesSize) {    
    int *values = (int*) malloc(pullUpValuesSize * sizeof(int));
    for (int i = 0; i < pullUpValuesSize; i++) {
        double voltage = (double)power * pullDown / (pullDown + pullUpValues[i]);
        values[i] = voltage / ((double)power / 1023); 
    }
    return ButtonSet(pin, values, pullUpValuesSize);
}

bool ButtonSet::update() {
    rawInput = analogRead(pin);
    int buttonIndex = determineButtonIndex(rawInput);
    return debouncer.update(buttonIndex);
}

int ButtonSet::get() {
	return debouncer.get();
}

int ButtonSet::getRaw() {
	return rawInput;
}

int ButtonSet::determineButtonIndex(int rawInput) {
  for (int i = 0; i < valuesSize; i++) {
    if (within(rawInput, values[i] - DELTA, values[i] + DELTA)) {
        return i + 1;
    }  
  }
  return 0;
}

bool ButtonSet::within(int value, int low, int high) {
    return low < value && value <= high;
}

