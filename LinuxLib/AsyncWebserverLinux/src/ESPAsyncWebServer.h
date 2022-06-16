#ifndef _ESPAsyncWebServer_H_
#define _ESPAsyncWebServer_H_

#include <functional>
#include <ArduinoJson.h>
#include <httpserver.hpp>

using namespace httpserver;

typedef enum {
  HTTP_GET     = 0b00000001,
  HTTP_POST    = 0b00000010,
  HTTP_DELETE  = 0b00000100,
  HTTP_PUT     = 0b00001000,
  HTTP_PATCH   = 0b00010000,
  HTTP_HEAD    = 0b00100000,
  HTTP_OPTIONS = 0b01000000,
  HTTP_ANY     = 0b01111111,
} WebRequestMethod;

typedef uint8_t WebRequestMethodComposite;

class AsyncWebServerRequest {
};
/*
 * FILTER :: Callback to filter AsyncWebRewrite and AsyncWebHandler (done by the Server)
 * */

typedef std::function<bool(AsyncWebServerRequest *request)> ArRequestFilterFunction;
typedef std::function<void(AsyncWebServerRequest *request, JsonVariant &json)> ArJsonRequestHandlerFunction;
typedef std::function<void(AsyncWebServerRequest *request)> ArRequestHandlerFunction;

class AsyncWebServer {
public:
    AsyncWebServer();
    AsyncWebServer(uint16_t port);
    void begin();
    void on(const char* uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest);
private:
    webserver ws;
};



#endif