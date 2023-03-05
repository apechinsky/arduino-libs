/*
  Debouncer library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

#include "Arduino.h"
#include "Debouncer.h"


Debouncer::Debouncer(unsigned long bounceDuration) {
    this->value = 0;
    this->bounceDuration = bounceDuration;
    this->lastValue = 0;
    this->lastValueTimestamp = 0;
}

bool Debouncer::update(int newValue) {

    if (newValue != lastValue) {
        lastValueTimestamp = millis();
    }

    bool changed = false;

    if (millis() - lastValueTimestamp > bounceDuration) {
        changed = newValue != value;

        if (changed) {
           value = newValue;
        }
    }

    lastValue = newValue;

    return changed;
}

int Debouncer::get() {
   return value;
}
