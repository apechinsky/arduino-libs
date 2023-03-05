/*
  SmartButton library
  Copyright (c) 2018 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

#ifndef Button_h
#define Button_h

// #include <inttypes.h>
#include "Debouncer.h"

/**
 * Button library recognizing click, multiple clicks and long press.
 * Each type of event is handle with handle function.
 *
 */
class Button {

public:

    /**
     * Constructs button set.
     *
     * @param pin analog pin number
     * @param pullUp
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

    typedef void (*OnClickedHandler)(void);

    typedef void (*OnMultipleClickingHandler)(int count);

    typedef void (*OnMultipleClickedHandler)(int count);

    typedef void (*OnLongPressedHandler)(int duration);


    /**
     * Define single click handler function.
     */
    void setOnClicked(OnClickedHandler handler);

    /**
     * Define handler which is called during user clicking a button
     */
    void setOnMultipleClicking(OnMultipleClickingHandler handler);

    /**
     * Define handler which is called when user finished clicking a button.
     */
    void setOnMultipleClicked(OnMultipleClickedHandler handler);

    /**
     * Define handler which is called when user released button after long press.
     */
    void setOnLongPressed(OnLongPressedHandler handler);


private:

    int pin;

    bool pullUp;

    Debouncer debouncer;


    unsigned long lastPressTime;

    unsigned long lastReleaseTime;

    bool pressed;

    int pressCount;


    void processStateChange(bool pressed);

    int getDuration(unsigned long start, unsigned long end);


    OnClickedHandler onClickedHandler = NULL;

    OnMultipleClickingHandler onMultipleClickingHandler = NULL;

    OnMultipleClickedHandler onMultipleClickedHandler = NULL;

    OnLongPressedHandler onLongPressedHandler = NULL;


    void onClicked();

    void onMultipleClicking(int count);

    void onMultipleClicked(int count);

    void onLongPressed(int duration);

};

#endif
