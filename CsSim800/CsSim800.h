#ifndef _CsSim800_H
#define _CsSim800_H

#include <SoftwareSerial.h>

#include "AtCommandDevice.h"

#include "Debug.h"

/** 
 * SIM800 GSM module controller.
 *
 * Simplifies SIM800 module programming by wrappginn AT commands to well named methods.
 */
class CsSim800 {

public:
    const String OK = "OK";
    const String FAIL = "FAIL";
    const String ERROR = "ERROR";
    const String CRLF = "\r\n";
    const String HTTP = "http://";

    const int DEFAULT_TIMEOUT = 5000;

    /** 
     * Generic constructor.
     *
     * @param stream a stream representing UART device
     *
     */
    CsSim800(Stream* stream, int resetPin);

    ~CsSim800();
  
    /**
     * Factory method creating an instance using SoftwareSerial
     */
    static CsSim800 softwareSerial(int receivePin, int transmitPin, int baudRate, int resetPin);

    /**
     * Returns SIM800 module version.
     */
    String getModuleVersion();

    /**
     * Returns Sim card identifier (IMEI).
     */
    String getIMEI();

    /**
     * Test if device is ready.
     */
    bool ping();

    /**
     * Reset device
     */
    bool reset();
    
    /**
     * Power down device.
     */
    void powerDown(); 

    /**
     * Enable/disable AT command echo.
     *
     * <p>Enabling echo causes more memory cunsumption during parsing response.
     * It's recommended to disable echo</p>
     */
    bool echo(bool enable);

    bool attach(unsigned long timeout);

    /**
     * Waits until device registers to GSM network.
     *
     * @timeout timeout in milliseconds
     * @return true on successful registration, false otherwise.
     */
    bool waitForNetwork(unsigned long timeout);

    bool setFullMode();


    bool sleepMode1();

    bool awakeFromMode1();
    
    bool sleepMode2();

    bool awakeFromMode2();

    bool disableSleepMode();

    bool setSleepMode(int mode);

    /**
     * Returns power supply voltage.
     *
     * @return value in mV
     */
    int getBatteryVoltage();

    /**
     * Return network registration status.
     * 
     * - 1 Registered
     * - 2 Registration in progress
     * - 3 Registration denied
     * - 4 Unknown
     * - 5 Registered, roaming
     *
     * - -1 Error
     */
    int getNetworkStatus();

    bool smsSend(const String &number, const String &text);

    /**
     * Returns IP that was assigned to module (available when GPRS connection is UP).
     */
    String getIP();

    bool gprsUp(const String &apn, const String &user, const String &password);

    bool gprsDown();

    bool gprsCloseSockets();

    bool httpGet(const String &host, int port, const String &data);

    bool httpGet(const String &url);

    void passThrough();

private:

    /** 
     * AT command managed device
     */
    AtCommandDevice *device;

    String buffer;

    int resetPin;

    int timeout = 2000;

    bool gprsEnableService(bool enable);

    bool gprsEnableBearer(bool enable);

    bool gprsSetApn(const String &apn, const String &user, const String &password);

    bool gprsConnectApn();
};

#endif
