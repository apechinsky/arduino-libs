#ifndef ThingSpeak_h
#define ThingSpeak_h

#include "HttpClient.h"

/**
 * ThingSpeak service client.
 *
 * Simplifies posting data to ThingSpeak channels.
 */
class ThingSpeak {

public:

    /**
     * Constructor.
     *
     * @param apiKey ThingSpeak write API key.
     * @param httpClient http client
     */
    ThingSpeak(const char *apiKey, HttpClient *httpClient);

    /**
     * Send single record (a list of values) to ThingSpeak service.
     *
     * @param values a pointer to float values
     * @param count values count
     */
    bool send(float* values, int count);

private:

    const char *apiKey;

    HttpClient *httpClient;
    
};

#endif
