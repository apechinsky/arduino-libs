/*
  Debouncer library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

#ifndef Debouncer_h
#define Debouncer_h

#include <inttypes.h>

/**
 * General purpose bounce protection class.
 * Unlike Debounce.cpp class this class doesn't read pin value itself so it can be used in any context.
 * 
 * Usage:
 * if (debouncer.update(newValue)) {
 *    // value has changed, use it directly or obtain via debouncer.get() method
 * } 
 *
 * @param bounceTime bounce time
 */
class Debouncer {

public:

   /**
    * Constructor.
    *
    * @param bounceTime bounce time
    */
    Debouncer(int bounceTime);

   /**
    * Update value.
    *
    * Performs main debounce logic. Changes value after bounce period is completed.
    *
    * @param newValue new value
    * @return true - if value has changed and get() method may be used to get new value. 
    *         false - value hasn't changed or bounce period isn't completed. get() method returns old value.
    */
    bool update(int newValue);

    /**
     * Returns current value.
     */
    int get();

  
private:
  int bounceTime;

  int value;

  unsigned long valueTimestamp;

};

#endif


