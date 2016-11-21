/*
  MHZ19 library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/
#include <MHZ19.h>

MHZ19 mhz19;

void setup() {
    mhz19.begin(A0, A1, 9600);
}

void loop() {
    int ppm = mhz19.readCO2();
    Serial.println(ppm);

    delay(10 * 1000);
}


