/*
  CircularBuffer library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License v3.

  See file LICENSE for further informations on licensing terms.
*/

/**
 * Demonstrate basic CircularBuffer usage.
 */ 

#include <CircularBuffer.h>

#define MAX_SIZE 10

CircularBuffer buffer(MAX_SIZE);

void setup() {
    Serial.begin(9600);

    Serial.println("Empty buffer: ");
    buffer.print();

    // add numbers until buffer is full
    for (char c = '0'; c <= '9'; c++) {
        buffer.add(c);
        buffer.print();
        Serial.print("contains('56789'): ");
        Serial.println(buffer.contains("56789"));
    }

    // continue adding letters to full buffer.
    // Observe how buffer removes oldest characters in favour of new ones
    for (char c = 'a'; c < 'a' + 10; c++) {
        Serial.print("Add extra char: ");
        buffer.add(c);
        buffer.print();
        Serial.print("contains('56789'): ");
        Serial.println(buffer.contains("56789"));
    }

}

void loop() {

    delay(1000);        
}
