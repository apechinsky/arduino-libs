#ifndef _AtCommandDevice_H
#define _AtCommandDevice_H

#include "Arduino.h"

/** 
 * Serial stream wrapper for simplifying interation with AT command devices.
 *  
 * Contains a set of methods for issuing AT command to underlying stream
 * and interpreting results.
 */
class AtCommandDevice {

public:
    const char *OK = "OK";

    const char *FAIL = "FAIL";

    const char *ERROR = "ERROR";

    const char *CR = "\r";

    const char *LF = "\n";

    const char *CRLF = "\r\n";

    const int DEFAULT_TIMEOUT = 5000;

    /** 
     * Generic constructor.
     *
     * @param stream a stream representing UART device
     */
    AtCommandDevice(Stream* stream);

    ~AtCommandDevice();
  
    /**
     * Factory method creating an instance using SoftwareSerial
     */
    static AtCommandDevice softwareSerial(int receivePin, int transmitPin, int baudRate);

    /**
     * Set default timeout.
     */
    void setTimeout(int timeout);

    /**
     * Read char from device.
     */
    char read();

    /**
     * Write char array to device.
     */
    void write(const char *command);

    /**
     * Overloaded version of write(const char*)
     */
    void write(const __FlashStringHelper *command);

    /**
     * Overloaded version of write(const char*)
     */
    void write(const String &command);

    void writeln(const char *command);

    void writeln(const __FlashStringHelper *command);

    void writeln(const String &command);

    bool sendAndWaitReply(const __FlashStringHelper *command);

    /**
     * Execute command and wait for result.
     */
    bool sendAndWaitReply(const char *command);

    String sendAndGetReply(const char *command);

    String sendAndGetReply(const __FlashStringHelper *command);

    /**
     * Write end mark symbol (0x1a) to device.
     */
    void sendEndMark();


    /**
     * Empty underlying stream buffer. 
     * Read until data available.
     */
    void empty();

    /**
     * Append data from device to read buffer until targetX is found.
     * 
     * @param strict 
     *      - true - repeat wait and read in a loop until targetX is found or timeout.
     *      - false - wait for data until timeout and read once. This function needed if command result 
     *        doesn't return OK mark (e.g. getIP)
     * @param target1 first target
     * @param target2 second target
     * @param timeout timeout in millis
     * @return
     *      -  0 - first target found
     *      -  1 - second target found
     *      - -1 - timeout
     *      - -2 - string=false and no target was found
     */
    int readUntil(bool strict, const String &target1, const String &target2, long timeout);

    int readUntilTarget(const String &target1, const String &target2, long timeout);

    int readUntilTargetOrAvailable(const String &target1, const String &target2, long timeout);


    bool readUntilOkOrError(long timeout);

    /**
     * Return string between 'start' and 'end' from read buffer.
     *
     * @param start - start string (nullable). If NULL use start of buffer.
     * @param end - end string (nullable). If NULL use end of buffer.
     * @return string value
     */
    String getOutput(const char *start, const char *end);

    /**
     * Return string between 'start' and 'end' from read buffer.
     *
     * Overloaded version of getOutput(const char*, const char*) with String parameters.
     */
    String getOutput(const String &start, const String &end);

    /**
     * Return string between 'start' and 'end' from read buffer.
     *
     * Overloaded version of getOutput(const char*, const char*) with Flash string (F() macro) parameters.
     */
    String getOutput(const __FlashStringHelper *start, const __FlashStringHelper *end);

    /**
     * Return entire buffer.
     */
    String getOutput();



    void passThrough();

private:

    /** 
     * Serial port for UART Communication
     */
    Stream* stream;

    String buffer;

    int timeout = 2000;

};

#endif
