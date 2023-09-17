/*
  Button library
  Copyright (c) 2023 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

/**
 * Demonstrate basic button usage.
 */ 

/**
 * Demonstrate basic button usage.
 */

#include <Button.h>

#define BUTTON_PIN 3

Button button(BUTTON_PIN, true);

void setup() {
    Serial.begin(9600);

    button.setOnPressed(onPressed);
    button.setOnReleased(onReleased);
    button.setOnClicked(onClicked);
    button.setOnMultipleClicked(onMultipleClicked);
    button.setOnLongPressed(onLongPressed);
}

void loop() {
    button.update();

    delay(10);
}

void onPressed(int count) {
    Serial.print("pressed. count: ");
    Serial.println(count);
}

void onReleased(int count) {
    Serial.print("released. count: ");
    Serial.println(count);
}

void onClicked(int count) {
    Serial.print("clicked. clount: ");
    Serial.println(count);
}

void onMultipleClicked(int count) {
    Serial.print("multiple clicked. count: ");
    Serial.println(count);
    Serial.println("-----------------------");
}

void onLongPressed(int duration) {
    Serial.print("long pressed. duration: ");
    Serial.println(duration);
    Serial.println("-----------------------");
}
