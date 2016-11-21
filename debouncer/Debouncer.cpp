/*
  Debouncer library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

#include "Arduino.h"
#include "Debouncer.h"


Debouncer::Debouncer(int bounceTime) {
    this->bounceTime = bounceTime;
    this->value = 0;
    this->valueTimestamp = 0;
}

bool Debouncer::update(int newValue) {

    bool valueChanged = newValue != value;
    bool bounceCompleted = millis() - valueTimestamp > bounceTime;

    if (valueChanged && bounceCompleted) {
        value = newValue;
        valueTimestamp = millis();
        return true;
    }
    return false;
}

int Debouncer::get() {
   return value;
}
