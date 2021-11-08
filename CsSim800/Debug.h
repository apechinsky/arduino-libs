#ifndef _Debug_H
#define _Debug_H

// #include "Arduino.h"
//
#define CS_SIM800_DEBUG

#ifdef CS_SIM800_DEBUG
    #define DEBUG_PRINT(...)		Serial.print(__VA_ARGS__)
    #define DEBUG_PRINTLN(...)		Serial.println(__VA_ARGS__)
    #define DEBUG_PRINT_RESULT(label, value)		Serial.print(label); Serial.println(value ? "OK" : "FAIL")
    #define DEBUG_PRINT_VALUE(label, value)		Serial.print(label); Serial.println(value)
#else 
    #define DEBUG_PRINT(...)
    #define DEBUG_PRINTLN(...)
    #define DEBUG_PRINT_RESULT(label, value)
    #define DEBUG_PRINT_VALUE(label, value)
#endif

#endif
