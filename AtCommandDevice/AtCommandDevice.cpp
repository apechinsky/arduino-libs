#include "AtCommandDevice.h"

#include <SoftwareSerial.h>
#include <StreamDebugger.h>

#include "Debug.h"


AtCommandDevice::AtCommandDevice(Stream *stream) {
    this->timeout = DEFAULT_TIMEOUT;

    this->stream = stream;

    this->buffer = String(128);
}

AtCommandDevice::~AtCommandDevice() {
    delete stream;
}

static AtCommandDevice AtCommandDevice::softwareSerial(int receivePin, int transmitPin, int baudRate) {
    Stream* stream = new SoftwareSerial(receivePin, transmitPin);
    return AtCommandDevice(stream);
}

void AtCommandDevice::setTimeout(int timeout) {
    this->timeout = timeout;
}

char AtCommandDevice::read() {
    return stream->read();
}

void AtCommandDevice::write(const char *command) {
    this->stream->print(command);
}

void AtCommandDevice::write(const __FlashStringHelper *command) {
    this->stream->print(command);
}

void AtCommandDevice::write(const String &command) {
    this->stream->print(command);
}

void AtCommandDevice::writeln(const char *command) {
    this->stream->println(command);
}

void AtCommandDevice::writeln(const __FlashStringHelper *command) {
    this->stream->println(command);
}

void AtCommandDevice::writeln(const String &command) {
    this->stream->println(command);
}

bool AtCommandDevice::sendAndWaitReply(const __FlashStringHelper *command) {
    DEBUG_PRINT(F("\ncommand("));
    DEBUG_PRINT(command);
    DEBUG_PRINTLN(") : ");

    empty();

    writeln(command);

    bool result = readUntilOkOrError(timeout);

    DEBUG_PRINT_RESULT("result:", result);

    return result;
}

bool AtCommandDevice::sendAndWaitReply(const char *command) {
    DEBUG_PRINT(F("\ncommand("));
    DEBUG_PRINT(command);
    DEBUG_PRINTLN(") : ");

    empty();

    stream->println(command);

    bool result = readUntilOkOrError(timeout);

    DEBUG_PRINT_RESULT("result:", result);

    return result;
}

String AtCommandDevice::sendAndGetReply(const __FlashStringHelper *command) {
    if (!sendAndWaitReply(command)) {
        return ERROR;
    }
    return getOutput(NULL, OK);
}

String AtCommandDevice::sendAndGetReply(const char *command) {
    if (!sendAndWaitReply(command)) {
        return ERROR;
    }
    return getOutput(NULL, OK);
}

void AtCommandDevice::empty() {
    buffer = "";

    while (stream->available() > 0) {
        char ch = read();
        // DEBUG_PRINT(ch);
    }
}

void AtCommandDevice::sendEndMark() {
    stream->println((char)26);
}


bool AtCommandDevice::readUntilOkOrError(long timeout) {
    return readUntilTarget(OK, ERROR, timeout) == 0;
}

int AtCommandDevice::readUntilTarget(const String &target1, const String &target2, long timeout) {
	return readUntil(true, target1, target2, timeout);
}

int AtCommandDevice::readUntilTargetOrAvailable(const String &target1, const String &target2, long timeout) {
	return readUntil(false, target1, target2, timeout);
}

int AtCommandDevice::readUntil(bool strict, const String &target1, const String &target2, long timeout) {

    unsigned long start = millis();

    // wait for the first chunk of data 
    while (millis() - start < timeout && !stream->available()) {
        delay(10);
    }

    while (millis() - start < timeout) {

        while (stream->available() > 0) {
            char ch = read();
            buffer += ch;

            if (buffer.indexOf(target1) != -1) {
                return 0;
            }

            if (buffer.indexOf(target2) != -1) {
                return 1;
            }
        }

        if (!strict) {
            return -2;
        }
    }

    return -1;
}

String AtCommandDevice::getOutput(const char *start, const char *end) {
    int startIndex = 0;

    if (start != NULL) {
        if (buffer.indexOf(start) == -1) {
            return "";
        }
        startIndex += strlen(start);
    }

    int endIndex = buffer.length();
    
    if (end != NULL) {
        endIndex = buffer.indexOf(end);
    }

    if (startIndex > endIndex) {
        return "";
    }
    
    String result = buffer.substring(startIndex, endIndex);
    result.trim();
    return result;
}

String AtCommandDevice::getOutput(const String &start, const String &end) {
    return getOutput(start.c_str(), end.c_str());
}

String AtCommandDevice::getOutput(const __FlashStringHelper *start, const __FlashStringHelper *end) {
    // TODO: Possibly no advantage of using FlashStringHelper since String is created
    // Convert to char* or implement getOutput() with PROGMEM functions *_P()
    return getOutput(String(start), String(end));
}

String AtCommandDevice::getOutput() {
    return getOutput((const char*)NULL, (const char*)NULL);
}

void AtCommandDevice::passThrough() {

    if (stream->available()){
        Serial.write(stream->read());
    }

    if (Serial.available()){     
        stream->write(Serial.read()); 
    }
}

