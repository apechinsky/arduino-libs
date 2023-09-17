/*
  Button library
  Copyright (c) 2023 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

#ifndef Button_h
#define Button_h

#include "Debouncer.h"

/**
 * Button class simplifies handling button events.
 *
 * The class recognizes the following event types:
 *  * press
 *  * release
 *  * click
 *  * long press
 *
 * Each event type is handled by a dedicated callback function.
 * See the documentation for the corresponding setOnXXX() function.
 *
 * Important! Some events are fired immediately, while others are not (see function documentation).
 * Developers should be cautious when handling both onClicked and onMultipleClicked events.
 * The onClicked event is fired each time a click is detected, but the onMultipleClicked
 * event is fired only once when the user stops clicking.
 */
class Button {

public:

    /**
     * Constructs button set.
     *
     * @param pin analog pin number
     * @param pullUp a flag indicated that button pin is pulled up and the class
     *  should register press event on LOW level.
     */
    Button(byte pin, bool pullUp);

    /**
     * Destructor.
     */
    virtual ~Button();

    /**
     * Read value from input, perform debounce logic and returns true if button was changed.
     */
    bool update();

    /**
     * Returns last changed button index (1-based)
     */
    bool isPressed();

    typedef void (*OnPressedHandler)(int count);

    typedef void (*OnReleasedHandler)(int count);

    typedef void (*OnClickedHandler)(int count);

    typedef void (*OnMultipleClickedHandler)(int count);

    typedef void (*OnLongPressedHandler)(int duration);

    /**
     * Define maximal duration between button clicks which will be
     * recognized as multiple click series.
     *
     * The click counter is reset if the duration exceeds the specified value.
     *
     * @param value max duration in milliseconds (default: 400ms)
     */
    void setMaxDurationBetweenClicks(int value);

    /**
     * Define the minimum duration between a press and release event that is recognized as a long press.
     *
     * @param value min duration in milliseconds (default: 600ms)
     */
    void setMinLongPressDuration(int value);

    /**
     * Define button 'press' handler function.
     * Handler is called imediately.
     */
    void setOnPressed(OnPressedHandler handler);

    /**
     * Define button 'release' handler function.
     * Handler is called imediately.
     */
    void setOnReleased(OnReleasedHandler handler);

    /**
     * Define button 'click' handler function.
     * Handler is called imediately.
     */
    void setOnClicked(OnClickedHandler handler);

    /**
     * Define button multiple click handler function.
     * Handler is called after some time is passed after last button release event.
     */
    void setOnMultipleClicked(OnMultipleClickedHandler handler);

    /**
     * Define long press button handler function.
     * Handler is called imediately after _single_ release button event.
     * The handler won't be called if a long press occurs in a multiple click series.
     */
    void setOnLongPressed(OnLongPressedHandler handler);


private:

    int pin;

    bool pullUp;

    int maxDurationBetweenClicks;

    long minLongPressDuration;

    Debouncer debouncer;

    int pressCount;

    unsigned long lastPressTime;

    unsigned long lastReleaseTime;

    bool pressed;

    /**
     * Checks if button has stopped clicked.
     *
     * Used to identify a moment when it's time to handle double, tripple, and
     * more click series.
     */
    bool isClickSeriesCompleted(unsigned long eventTime);

    void processStateChange(bool pressed, unsigned long eventTime);

    void processPressEvent(unsigned long eventTime);

    void processReleaseEvent(unsigned long eventTime);

    int getDuration(unsigned long start, unsigned long end);


    OnPressedHandler onPressedHandler = NULL;

    OnReleasedHandler onReleasedHandler = NULL;

    OnClickedHandler onClickedHandler = NULL;

    OnMultipleClickedHandler onMultipleClickedHandler = NULL;

    OnLongPressedHandler onLongPressedHandler = NULL;


    void onPressed(int count);

    void onReleased(int count);

    void onClicked(int count);

    void onMultipleClicked(int count);

    void onLongPressed(int duration);

    void printState(unsigned long eventTime);
};

#endif
