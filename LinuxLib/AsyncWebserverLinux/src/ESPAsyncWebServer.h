#ifndef _ESPAsyncWebServer_H_
#define _ESPAsyncWebServer_H_

#include <functional>
#include <ArduinoJson.h>
#include <httpserver.hpp>
#include <vector>
#include <memory>

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

class AsyncWebServerResponse {
  public:
  void setLength() {}; //TODO
  JsonVariant getRoot() {return ArduinoJson::JsonVariant();}; //TODO
};

class AsyncJsonResponse: public AsyncWebServerResponse
{
  public:
  AsyncJsonResponse(bool isArray=false, size_t maxJsonBufferSize = 1024) {}; //TODO
};

class AsyncWebServerRequest;
/*
 * FILTER :: Callback to filter AsyncWebRewrite and AsyncWebHandler (done by the Server)
 * */

typedef std::function<bool(AsyncWebServerRequest *request)> ArRequestFilterFunction;
typedef std::function<void(AsyncWebServerRequest *request, JsonVariant &json)> ArJsonRequestHandlerFunction;
typedef std::function<void(AsyncWebServerRequest *request)> ArRequestHandlerFunction;
typedef std::function<void(void)> ArDisconnectHandler;

class AsyncWebServerRequest : public http_resource{
  public:
    AsyncWebServerRequest(ArRequestHandlerFunction onRequest);
    const std::shared_ptr<http_response> render(const http_request&) override;
    void send(int status) {};//TODO
    void send(AsyncWebServerResponse response){};//TODO
    void send(AsyncJsonResponse response){};//TODO
    void onDisconnect (ArDisconnectHandler fn) {};//TODO
  private:
    ArRequestHandlerFunction m_fun;
};

class AsyncWebHandler
{
};

class AsyncCallbackJsonWebHandler: public AsyncWebHandler
{
  public:
  AsyncCallbackJsonWebHandler(const char* uri, ArJsonRequestHandlerFunction onRequest, size_t maxJsonBufferSize=1024) {};//TODO
  AsyncCallbackJsonWebHandler(const String& uri, ArJsonRequestHandlerFunction onRequest, size_t maxJsonBufferSize=1024) {};//TODO
  void setMethod(WebRequestMethodComposite method){}; //TODO
};

class AsyncWebServer {
public:
    AsyncWebServer();
    AsyncWebServer(uint16_t port);
    void begin();
    void on(const char* uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest);
    AsyncWebHandler& addHandler(AsyncWebHandler* handler) {};//TODO
private:
    const char* getMethodName(WebRequestMethodComposite method);
    
    webserver ws;
    std::vector<AsyncWebServerRequest*> m_requestVec;
};



#endif