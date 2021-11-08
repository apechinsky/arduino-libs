/*
  MHZ19 library
  Copyright (c) 2016 Anton Pechinsky.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the Apache License v2.0.

  See file LICENSE for further informations on licensing terms.
*/

#include "MHZ19.h"
#include <stdlib.h>

MHZ19::MHZ19() {
}

MHZ19::~MHZ19() {
    // TODO: remove created SoftwareSerial instance
}

void MHZ19::begin(int baudRate) {
    Serial.begin(baudRate);
    serial = &Serial;
}

void MHZ19::begin(uint8_t tx, uint8_t rx, int baudRate) {
    SoftwareSerial* softwareSerial = new SoftwareSerial(tx, rx);
    softwareSerial->begin(baudRate);

    serial = softwareSerial;
}

void MHZ19::begin(Stream &stream) {
    serial = &stream;
}

int MHZ19::readCO2() {
    unsigned char response[9];

    serial->write(MHZ19_CMD_READ_CO2, 9);
    memset(response, 0, 9);
    serial->readBytes(response, 9);

    byte crc = getCheckSum(response);

    if ( crc != response[8]) {
    //    Serial.print("CRC error: ");
    //    Serial.print(crc);
    //    Serial.print(" response: ");
    //    Serial.print(response[8]);
        return -1;
    } 

    int responseHigh = (int) response[2];
    int responseLow = (int) response[3];
    int ppm = (256 * responseHigh) + responseLow;
    return ppm;
}

byte MHZ19::getCheckSum(unsigned char *packet) {
    byte checksum = 0;
    for (int i = 1; i < 8; i++) { 
        checksum += packet[i];
    }
    return 255 - checksum + 1;
}

void MHZ19::calibrateZero() {
   unsigned char response[9];
   serial->write(MHZ19_CMD_CALIBRATE_ZERO, 9);
}

void MHZ19::calibrateSpan() {
    // TBD
}


