/*
  SmartButton library
  Copyright (c) 2023 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

#include "Arduino.h"
#include "Button.h"
#include "Debouncer.h"

#define DEFAULT_BOUNCE_TIME 50

#define DEFAULT_MAX_DURATION_BETWEEN_CLICKS 400

#define DEFAULT_MIN_LONG_PRESS_DURATION 600


Button::Button(byte pin, bool pullUp)
    : debouncer(DEFAULT_BOUNCE_TIME) {

    this->pin = pin;
    this->pullUp = pullUp;
    this->pressCount = 0;
    this->pressed = false;
    this->maxDurationBetweenClicks = DEFAULT_MAX_DURATION_BETWEEN_CLICKS;
    this->minLongPressDuration = DEFAULT_MIN_LONG_PRESS_DURATION;

    pinMode(pin, pullUp ? INPUT_PULLUP : INPUT);
}

Button::~Button() {
}

bool Button::update() {
    bool value = digitalRead(pin);

    unsigned long eventTime = millis();

    bool pressed = pullUp ? !value : value;

    bool changed = debouncer.update(pressed);

    if (changed) {
        processStateChange(pressed, eventTime);
    }
    else if (isClickSeriesCompleted(eventTime)) {
        onMultipleClicked(pressCount);
        pressCount = 0;
    }

    return changed;
}

bool Button::isClickSeriesCompleted(unsigned long eventTime) {
    return !pressed && pressCount > 0 && getDuration(lastReleaseTime, eventTime) >= maxDurationBetweenClicks;
}

void Button::processStateChange(bool pressed, unsigned long eventTime) {
    this->pressed = pressed;

    if (pressed) {
        processPressEvent(eventTime);
    }
    else {
        processReleaseEvent(eventTime);
    }
}

void Button::processPressEvent(unsigned long eventTime) {
    if (pressCount == 0) {
        lastPressTime = eventTime;
    }

    pressCount++;
    lastPressTime = eventTime;

    onPressed(pressCount);
}

void Button::processReleaseEvent(unsigned long eventTime) {
    int pressDuration = getDuration(lastPressTime, eventTime);

    lastReleaseTime = eventTime;

    onReleased(pressCount);

    if (pressCount == 1 && pressDuration >= minLongPressDuration) {
        onLongPressed(pressDuration);
        pressCount = 0;
    }
    else {
        onClicked(pressCount);
    }
}

void Button::setOnPressed(OnPressedHandler handler) {
    onPressedHandler = handler;
}

void Button::setOnReleased(OnReleasedHandler handler) {
    onReleasedHandler = handler;
}

void Button::setOnClicked(OnClickedHandler handler) {
    onClickedHandler = handler;
}

void Button::setOnMultipleClicked(OnMultipleClickedHandler handler) {
    onMultipleClickedHandler = handler;
}

void Button::setOnLongPressed(OnLongPressedHandler handler) {
    onLongPressedHandler = handler;
}

void Button::onPressed(int count) {
    if (onPressedHandler) {
        onPressedHandler(count);
    }
}

void Button::onReleased(int count) {
    if (onReleasedHandler) {
        onReleasedHandler(count);
    }
}

void Button::onClicked(int count) {
    if (onClickedHandler) {
        onClickedHandler(count);
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

void Button::printState(unsigned long eventTime) {
    Serial.print("Button [");
    Serial.print(" eventTime: ");
    Serial.print(eventTime);
    Serial.print(" pressed: ");
    Serial.print(pressed);
    Serial.print(" pressCount: ");
    Serial.print(pressCount);
    Serial.print(" lastPressTime: ");
    Serial.print(lastPressTime);
    Serial.println();
}

