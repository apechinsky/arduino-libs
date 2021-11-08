#ifndef _HttpClient_h
#define _HttpClient_h

/**
 * Simple HTTP client interface.
 */
class HttpClient {

public:

    /**
     * Execute HTTP get method.
     *
     * @param url - url to excute
     * @return true if call was successful
     */
    virtual bool get(const char *url);

};

#endif
