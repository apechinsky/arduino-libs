#include "Sim800HttpClient.h"

Sim800HttpClient::Sim800HttpClient(CsSim800 *sim800) {
    this->sim800 = sim800;
}

bool Sim800HttpClient::get(const char *url) {
    return sim800->httpGet(url);
}


