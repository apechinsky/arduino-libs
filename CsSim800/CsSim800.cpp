#include "CsSim800.h"

#include "Arduino.h"
#include <StreamDebugger.h>
// #include "Debug.h"

#define HTTP_PORT 80

CsSim800::CsSim800(Stream *stream, int resetPin) {
    this->timeout = DEFAULT_TIMEOUT;

    this->resetPin = resetPin;

    this->buffer = String(128);

    Stream *effectiveStream = stream;

    effectiveStream = new StreamDebugger(*stream, Serial);

    this->device = new AtCommandDevice(effectiveStream);

    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, HIGH);
}

CsSim800::~CsSim800() {
    delete device;
}

static CsSim800 CsSim800::softwareSerial(int receivePin, int transmitPin, int baudRate, int resetPin) {
    Stream* stream = new SoftwareSerial(receivePin, transmitPin);
    return CsSim800(stream, resetPin);
}

bool CsSim800::ping() {
    return device->sendAndWaitReply(F("AT"));
}

bool CsSim800::reset() {
    DEBUG_PRINTLN(F("Reset SIM800"));

    digitalWrite(resetPin, LOW); 
    delay(1000);
    digitalWrite(resetPin, HIGH); 
}

/**
 * Performs normal power down.
 */
void CsSim800::powerDown() {
    DEBUG_PRINTLN(F("Power down SIM800"));

    device->empty();

    // 0 - Power off urgently (Will not send out NORMAL POWER DOWN)
    // 1 - Normal power off (Will send out NORMAL POWER DOWN)
    device->writeln(F("AT+CPOWD=1"));
}

bool CsSim800::echo(bool enable) {
    char buffer[10];

    snprintf_P(buffer, sizeof(buffer), PSTR("ATE%d"), enable ? 1 : 0);

    return device->sendAndWaitReply(buffer);
}

bool CsSim800::attach(unsigned long timeout) {

    unsigned long start = millis();

    DEBUG_PRINTLN(F("Waiting module..."));

	while (!ping()) {
		DEBUG_PRINTLN(F("Failed. Waiting..."));

		delay(1000);

        if (millis() - start >= timeout) {
            return false;
        }
	}

    DEBUG_PRINTLN(F("Module found."));

    if (!echo(false)) {
        DEBUG_PRINTLN(F("Disable echo failed..."));
        return false;
    }

    DEBUG_PRINTLN(F("Module ready."));

    return true;
}


bool CsSim800::waitForNetwork(unsigned long timeout) {
    unsigned long start = millis();

    if (!attach(timeout)) {
        return false;
    }

    DEBUG_PRINTLN(F("Waiting network..."));

	while (getNetworkStatus() != 1) {

		DEBUG_PRINTLN(F("No network. Waiting..."));
        
        if (millis() - start >= timeout) {
            return false;
        }

		delay(1000);
	}

    DEBUG_PRINTLN(F("Network ready."));

    return true;
}

String CsSim800::getModuleVersion() {
    return device->sendAndGetReply(F("ATI"));
}

String CsSim800::getIMEI() {
    return device->sendAndGetReply(F("AT+GSN"));
}

bool CsSim800::setFullMode() {
    return device->sendAndWaitReply(F("AT+CFUN=1"));
}

bool CsSim800::sleepMode1() {
    return setSleepMode(1);
}

bool CsSim800::awakeFromMode1() {
    // pull down DTR pin for 50ms
    return true;
}

bool CsSim800::sleepMode2() {
    return setSleepMode(2);
}

bool CsSim800::awakeFromMode2() {
    // send ping to wake up module from mode 2
    // response will be lost
    ping();
    return true;
}

bool CsSim800::disableSleepMode() {
    return setSleepMode(0);
}

bool CsSim800::setSleepMode(int mode) {
    char buffer[15];

    snprintf_P(buffer, sizeof(buffer), PSTR("AT+CSCLK=%d"), mode);

	return device->sendAndWaitReply(buffer);
}

int CsSim800::getBatteryVoltage() {
    device->empty();

    device->writeln(F("AT+CBC"));
    
    int index = device->readUntilTargetOrAvailable(OK, ERROR, timeout);

    if (index != 0) {
        return -1;
    }

    String response = device->getOutput(F("CBC:"), F("OK"));

	int lastComma = response.lastIndexOf(',');

	if (lastComma == -1) {
		return -1;
	}

	return response.substring(lastComma + 1).toInt();
}

int CsSim800::getNetworkStatus() {
	device->empty();

	device->writeln(F("AT+CREG?"));

    int index = device->readUntilTargetOrAvailable(OK, ERROR, timeout);

    if (index != 0) {
        return -1;
    }

    String response = device->getOutput(F("CREG:"), OK);

	int lastComma = response.lastIndexOf(',');

	if (lastComma == -1) {
		return -1;
	}

	return response.substring(lastComma + 1).toInt();
	
}

bool CsSim800::smsSend(const String &number, const String &text) {
    device->empty();

    // Set charset to GSM
    if (!device->sendAndGetReply(F("AT+CSCS=GSM"))) {
		return false;
	}

    // Choose text sms format
    if (!device->sendAndGetReply(F("AT+CMGF=1"))) {
		return false;
	}

    char buffer[15];
	snprintf_P(buffer, sizeof(buffer), PSTR("AT+CMGS=\"%s\""), number.c_str());
	device->writeln(buffer);

    int index = device->readUntilTarget(">", ERROR, timeout);
	if (index != 0) {
		return false;
	}

	device->writeln(text);

	device->sendEndMark();

	return device->readUntilOkOrError(timeout);
}

String CsSim800::getIP() {
    device->empty();

    device->writeln(F("AT+CIFSR"));
    
    int index = device->readUntilTargetOrAvailable(OK, ERROR, timeout);

    if (index != -2) {
        return ERROR;
    }

    return device->getOutput();
}

bool CsSim800::gprsUp(const String &apn, const String &user, const String &password) {

    if (!gprsCloseSockets()) {
        return false;
    }

    if (!gprsEnableService(true)) {
        return false;
    }

    if (!gprsSetApn(apn, user, password)) {
        return false;
    }

    if (!gprsConnectApn()) {
        return false;
    }

    if (!getIP()) {
        return false;
    }
    return true;
}

bool CsSim800::httpGet(const String &url) {

	if (!url.startsWith(HTTP)) {
		return false;
	}

	int hostStartIndex = HTTP.length();
	int pathStartIndex = url.indexOf("/", hostStartIndex);
	int colonStart = url.indexOf(":", hostStartIndex);

	int hostEnd = colonStart == -1 ? pathStartIndex : colonStart;
	String host = url.substring(hostStartIndex, hostEnd);

	String path = url.substring(pathStartIndex);
	int port  = colonStart != -1 
		? url.substring(colonStart, pathStartIndex).toInt()
		: HTTP_PORT;
	
	String request;
	request += "GET ";
	request += path;
	request += " HTTP/1.1";
	request += CRLF;
	request += "Host: ";
	request += host;
	request += CRLF;
	request += CRLF;

	return httpGet(host, port, request);
}

bool CsSim800::httpGet(const String &host, int port, const String &request) {
	device->empty();

    char buffer[50];

	// Establish TCP connection
    snprintf_P(buffer, sizeof(buffer), PSTR("AT+CIPSTART=\"TCP\",\"%s\",\"%d\""), host.c_str(), port);
    device->writeln(buffer);

	if (device->readUntilTarget("CONNECT OK", ERROR, timeout) != 0) {
		return false;
	}

	// send packet size
	// device->writeln("AT+CIPSEND");
    snprintf_P(buffer, sizeof(buffer), PSTR("AT+CIPSEND=%d"), request.length());
    device->writeln(buffer);

	// wait for prompt
	if (device->readUntilTarget(">", ERROR, timeout) != 0) {
		return false;
	}
	
	// send HTTP request
	if (!device->sendAndWaitReply(request.c_str())) {
		return false;
	}

	// close TCP connection
	if (!device->sendAndWaitReply(F("AT+CIPCLOSE"))) {
		return false;
	}

	return true;
}

bool CsSim800::gprsDown() {

    if (!gprsCloseSockets()) {
        return false;
    }

    if (!gprsEnableService(false)) {
        return false;
    }

    return true;
}

bool CsSim800::gprsEnableService(bool enable) {
    device->empty();

    char buffer[20];
    snprintf_P(buffer, sizeof(buffer), PSTR("AT+CGATT=%d"), enable); 
    device->writeln(buffer);
    
    return device->readUntilOkOrError(timeout * 3);
}

bool CsSim800::gprsEnableBearer(bool enable) {
    if (enable) {

        if (!device->sendAndWaitReply(F("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""))) {
            return false;
        }
 
        if (!device->sendAndWaitReply(F("AT+SAPBR=1,1"))) {
            return false;
        }
    }
    else {
        if (!device->sendAndWaitReply(F("AT+SAPBR=0,1"))) {
            return false;
        }
    }

    return true;
}

bool CsSim800::gprsSetApn(const String &apn, const String &user, const String &password) {
    device->empty();

    char buffer[50];

    snprintf_P(buffer, sizeof(buffer), PSTR("AT+CSTT=\"%s\",\"%s\",\"%s\""), apn.c_str(), user.c_str(), password.c_str());
    device->writeln(buffer);

    return device->readUntilOkOrError(timeout);
}

bool CsSim800::gprsConnectApn() {
    return device->sendAndWaitReply(F("AT+CIICR"));
}

bool CsSim800::gprsCloseSockets() {
    return device->sendAndWaitReply(F("AT+CIPSHUT"));
}

void CsSim800::passThrough() {
    device->passThrough();
}

