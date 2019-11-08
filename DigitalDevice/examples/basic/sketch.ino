/*
  DigitalDevice library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License v3.

  See file LICENSE for further informations on licensing terms.
*/

/**
 * Demonstrate basic DigitalDevice usage.
 */ 

#include <DigitalDevice.h>

#define DEFAULT_BOUNCE_TIME 100

DigitalDevice button = DigitalDevice::output(7, "button");

DigitalDevice lamp = DigitalDevice::output(8, "lamp");

void setup() {
}

void loop() {

    int buttonOn = button.get();

    lamp.set(buttonOn);

    delay(100);        
}
