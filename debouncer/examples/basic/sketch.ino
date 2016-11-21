/*
  Debouncer library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

/**
 * Demonstrate basic debouncer usage.
 */ 

#include <Debouncer.h>

#define BUTTON_PIN D1

#define DEFAULT_BOUNCE_TIME 100

Debouncer debouncer(DEFAULT_BOUNCE_TIME);

void setup() {
    pinMode(D1, INPUT);
}

void loop() {
    int pinState = digitalRead(BUTTON_PIN);

    bool stateChanged = debouncer.update(pinState);

    if (stateChanged) {
        Serial.print("button:");
        Serial.println(debouncer.get());
    }

    delay(10);
}


