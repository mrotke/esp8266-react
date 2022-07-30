#ifndef _ESPAsyncWebServer_H_
#define _ESPAsyncWebServer_H_

#include <functional>
#include <ArduinoJson.h>
#include <httpserver.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

using namespace httpserver;
using namespace std;

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

class AsyncWebParameter
{
  public:
    AsyncWebParameter(){};
    const String& value() {return m_value;};//TODO
  private:
    String m_value;
};

class AsyncWebHeader
{
  public:
    AsyncWebHeader(){};
    const String& value() {return m_value;};//TODO
  private:
    String m_value;
};

class AsyncWebServerRequest : public http_resource{
  public:
    AsyncWebServerRequest(ArRequestHandlerFunction onRequest) {}; //TODO
    const std::shared_ptr<http_response> render(const http_request&) override;
    void send(int status) {};//TODO
    void send(AsyncWebServerResponse response){};//TODO
    void send(AsyncJsonResponse response){};//TODO
    void onDisconnect (ArDisconnectHandler fn) {};//TODO
    AsyncWebServerResponse *beginResponse(int code){ return nullptr;}; //TODO
    AsyncWebHeader* getHeader(const String& name) const {return nullptr;}; //TODO
    bool hasParam(const String& name) const {return false;}; //TODO
    AsyncWebParameter* getParam(const String& name) const {return nullptr;}; //TODO
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
  void setMaxContentLength(int maxContentLength){};
};

class AsyncWebServer {
public:
    AsyncWebServer();
    AsyncWebServer(unsigned short port);
    void begin();
    void on(const char* uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest);
    AsyncWebHandler& addHandler(AsyncWebHandler* handler) { return *handler;};//TODO
private:
    const char* getMethodName(WebRequestMethodComposite method);
    
    unique_ptr<webserver> ws = nullptr;
    vector<AsyncWebServerRequest*> m_requestVec;
    unordered_map<string, AsyncWebServerRequest*> m_handlerMap;
};



#endif