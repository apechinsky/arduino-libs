#include "ThingSpeak.h"
#include "Arduino.h"
#include "Debug.h"

const char HTTP[] PROGMEM = "http";
const char HTTPS[] PROGMEM = "https";
const char URL_PATTERN[] PROGMEM = "%S://api.thingspeak.com/update?api_key=%s";

ThingSpeak::ThingSpeak(const char *apiKey, HttpClient *httpClient) {
    this->apiKey = apiKey;
    this->httpClient = httpClient;
}

bool ThingSpeak::send(float* values, int count) {

    char request[150];

    char fieldBuffer[15];

    char valueBuffer[20];

    snprintf_P(request, sizeof(request), URL_PATTERN, HTTP, apiKey);

    for (int i = 0; i < count; i++) {

        snprintf_P(fieldBuffer, sizeof(fieldBuffer), PSTR("&field%d="), i + 1);

        char* valueString = dtostrf(values[i], 4, 2, valueBuffer);
        strncat(fieldBuffer, valueString, strlen(valueString));

        int requestFreeBytes = sizeof(request) - strlen(request);

        strncat(request, fieldBuffer, requestFreeBytes);
    } 

    return httpClient->get(request);
}


