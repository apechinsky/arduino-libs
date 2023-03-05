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

#include <Button.h>

#define BUTTON_PIN 3

#define DEFAULT_BOUNCE_TIME 100

Button button(BUTTON_PIN, true);

void setup() {
    button.setOnClicked(onButtonClick);
    button.setOnMultipleClicking(onButtonClicking);
    button.setOnMultipleClicked(onButtonClicked);
    button.setOnLongPressed(onButtonLongPressed);
}

void loop() {
    button.update();

    delay(10);
}

void onButtonClick() {
    Serial.println("button click");
}

void onButtonClicking(int count) {
    Serial.print("button clicking ");
    Serial.println(count);
}

void onButtonClicked(int count) {
    Serial.print("button clicked ");
    Serial.println(count);
}

void onButtonLongPressed(int duration) {
    Serial.print("button clicked ");
    Serial.println(count);
}

