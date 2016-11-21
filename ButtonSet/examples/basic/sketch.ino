/*
  ButtonSet library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License v3.

  See file LICENSE for further informations on licensing terms.
*/

/**
 * Demonstrate basic ButtonSet usage.
 */ 

#include <ButtonSet.h>

#define DEFAULT_BOUNCE_TIME 100

int values[] = {0, 1, 2, 3, 4, 5, 6, 7}; 
ButtonSet buttonSet1 = ButtonSet::createWithValues(A1, values, sizeof(values) / sizeof(int));

int values[] = {0, 1, 2, 3, 4, 5, 6, 7}; 
ButtonSet buttonSet2= ButtonSet::createWithResistors(A2, 5, 5, values, sizeof(values) / sizeof(int));

void setup() {
}

void loop() {
    if (buttonSet1.update()) {
        Serial.print("buttonSet1 index: ");
        Serial.println(buttonSet.get());
    }

    if (buttonSet2.update()) {
        Serial.print("buttonSet2 index: ");
        Serial.println(buttonSet.get());
    }

    delay(100);        
}
