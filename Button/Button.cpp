/*
  SmartButton library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

#include "Arduino.h"
#include "Button.h"
#include "Debouncer.h"

#define DEFAULT_BOUNCE_TIME 100

#define SERIES_INTERVAL 600

#define LONG_PRESS_DURATION 1000


Button::Button(byte pin, bool pullUp) 
    : debouncer(DEFAULT_BOUNCE_TIME) {

    this->pin = pin;
    this->pullUp = pullUp;
    this->pressCount = 0;

    pinMode(pin, pullUp ? INPUT_PULLUP : INPUT);
}

Button::~Button() {
}

bool Button::update() {
    bool value  = digitalRead(pin);


    // invert value for pullUp PIN
    bool pressed = pullUp ? !value : value;

    bool changed = debouncer.update(pressed);

    if (changed) {
        processStateChange(pressed);
    }
    else if (pressCount > 0 && getDuration(lastReleaseTime, millis()) > SERIES_INTERVAL) {
        if (pressCount > 1) {
            onMultipleClicked(pressCount);
        }
        else {
            onClicked();
        }
        pressCount = 0;
    }


    return changed;
}

void Button::processStateChange(bool pressed) {
    unsigned long thisEventTime = millis();

    this->pressed = pressed;

    if (pressed) {
        lastPressTime = thisEventTime;

        if (getDuration(lastReleaseTime, thisEventTime) >= SERIES_INTERVAL) {
            pressCount = 0;
        }
    }
    else { 
        pressCount++;

        int pressDuration = getDuration(lastPressTime, thisEventTime);

        if (pressDuration >= SERIES_INTERVAL) {
            pressCount = 0;
            onLongPressed(pressDuration);
        }
        else if (getDuration(lastReleaseTime, thisEventTime) < SERIES_INTERVAL) {
            onMultipleClicking(pressCount);
        }

        lastReleaseTime = thisEventTime;
    }

}

void Button::setOnClicked(OnClickedHandler handler) {
    onClickedHandler = handler;
}

void Button::setOnMultipleClicking(OnMultipleClickingHandler handler) {
    onMultipleClickingHandler = handler;
}

void Button::setOnMultipleClicked(OnMultipleClickedHandler handler) {
    onMultipleClickedHandler = handler;
}

void Button::setOnLongPressed(OnLongPressedHandler handler) {
    onLongPressedHandler = handler;
}

void Button::onClicked() {
    if (onClickedHandler) {
        onClickedHandler();
    }
}

void Button::onMultipleClicking(int count) {
    if (onMultipleClickingHandler) {
        onMultipleClickingHandler(count);
    }
}

void Button::onMultipleClicked(int count) {
    if (onMultipleClickedHandler) {
        onMultipleClickedHandler(count);
    }
}

void Button::onLongPressed(int duration) {
    if (onLongPressedHandler) {
        onLongPressedHandler(duration);
    }
}


bool Button::isPressed() {
    return debouncer.get();
}

int Button::getDuration(unsigned long start, unsigned long end) {
    // TODO: check for overflow
    return end - start;
}

