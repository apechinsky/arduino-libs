/*
  MHZ19 library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/
 
#ifndef MHZ19_h
#define MHZ19_h

#include <Arduino.h>
#include <Stream.h>
#include <SoftwareSerial.h>
#include <avr/pgmspace.h>

const byte MHZ19_CMD_READ_CO2[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; 

const byte MHZ19_CMD_CALIBRATE_ZERO[9] = {0xFF,0x01,0x87,0x00,0x00,0x00,0x00,0x00,0x78}; 

class MHZ19 {

public:
    MHZ19();

    ~MHZ19();

    /**
     * Init sensor with provided stream instance.
     * 
     * // init with hardware serial
     * mhz19.begin(&Serial);
     *
     * // init with previously created software serial
     * mhz19.begin(serial);
     */
    void begin(Stream &stream);
   
    /**
     * Init sensor with RX, TX pins. Implementation creates SoftwareSerial.
     */
    void begin(uint8_t txPin, uint8_t rxPin, int baudRate);

    /**
     * Init sensor with Hardware serial.
     */
    void begin(int baudRate);

    /**
     * Read PPM value from sensor.
     */
    int readCO2();

    /**
     * Calibrate sensor to Zero point.
     */
    void calibrateZero();

    /**
     * Calibrate sensor's span points.
     */
    void calibrateSpan();

private:
    Stream* serial;

    byte getCheckSum(unsigned char *packet); 
};

#endif
