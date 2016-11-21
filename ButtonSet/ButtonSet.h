/*
  ButtonSet library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

#ifndef ButtonSet_h
#define ButtonSet_h

#include <inttypes.h>
#include "Debouncer.h"

/**
 * ButtonSet allows to attach multiple buttons to single analog pin.
 * 
 * Class features:
 *   - reads input
 *   - determines button index (1-based) basing on provided values array 
 *   - debounce value
 */ 
class ButtonSet {

public:

  /**
   * Constructs button set.
   *   
   * @param pin analog pin number
   * @param values array of analog input border values which are split interval [0-1023].
   * @param valuesSize size of array
   */
  ButtonSet(byte pin, int* values, int valuesSize);

  /**
   * Destructor.
   */
  virtual ~ButtonSet();

  /**
   * Creates an instance with analog values. Values should be computed or obtained experimentally.
   * 
   * Example. Serve 6 buttons connected to analog pin.
   * int values[] = {0, 200, 400, 600, 800, 1000};
   * ButtonSet buttonSet = ButtonSet::createWithValues(ANALOG_PIN, values, sizeof(values) / sizeof(int)); 
   *
   * @param pin analog pin number
   * @param values an array of int values (0-1024). Each value associated with separate button.
   * @param valuesSize size of 'values' array
   */
  static ButtonSet createWithValues(byte pin, int* values, int valuesSize); 

  /**
   * Creates an instance with resistor values.
   * Method coumputes analog values for each resistor value authomatically.
   * 
   * Example. Serve 8 buttons connected to analog pin.
   * int values[] = {0, 1, 2, 3, 4, 5, 6, 7}; 
   * ButtonSet buttonSet = ButtonSet::createWithResistors(ANALOG_PIN, 5, 5, values, sizeof(values) / sizeof(int));
   *
   * @param pin analog pin number
   * @param power power value (volts)
   * @param pullDown ???
   * @param pullUpValues an array of resisteor values (kOm).
   * @param pullUpValuesSize size of 'pullUpValues' array
   */
  static ButtonSet createWithResistors(byte pin, int power, int pullDown, int* pullUpValues, int pullUpValuesSize);

  /**
   * Read value from input, perform debounce logic and returns true if button was changed.
   */
  bool update();

  /**
   * Returns last changed button index (1-based)
   */
  int get();

  /**
   * Returns last raw value of analog pin.
   */
  int getRaw();
  
private:
  int *values;

  int valuesSize;

  int pin;

  int rawInput;

  Debouncer debouncer;

  Debouncer* d;

  int determineButtonIndex(int rawInput);

  bool within(int value, int low, int high);
};

#endif
