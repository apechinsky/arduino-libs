#ifndef _Sim800HttpClient_h
#define _Sim800HttpClient_h

#include "HttpClient.h"
#include "CsSim800.h"

/**
 * An implementation of HttpClient based on SIM800 GSM module.
 */
class Sim800HttpClient : public HttpClient {

public:
    Sim800HttpClient(CsSim800 *sim800);

    virtual bool get(const char *url);

private:
    CsSim800 *sim800;

};

#endif
