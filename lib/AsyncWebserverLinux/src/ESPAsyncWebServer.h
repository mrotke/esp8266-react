#ifndef _ESPAsyncWebServer_H_
#define _ESPAsyncWebServer_H_

#include <functional>
#include <ArduinoJson.h>
#include <httpserver.hpp>
#include <unordered_map>
#include <map>
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
  AsyncWebServerResponse() {};
  AsyncWebServerResponse( int code) { m_code = code;};
  void setLength() {};
  int GetCode() const {return m_code;};
  const string& GetContentType() const { return m_contentType;};
  virtual const string GetContent() const {return string("");};
  protected:
  string m_contentType = "text/plain";
  int m_code = 200;

};

class AsyncJsonResponse: public AsyncWebServerResponse
{
  public:
  AsyncJsonResponse(bool isArray=false, size_t maxJsonBufferSize = 1024);
  JsonVariant getRoot() {return m_root;};
  const string GetContent() const override;
  private:
  DynamicJsonDocument m_JSONBuffer;
  JsonVariant m_root;
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
    const String& value() {return m_value;};
    void SetValue(string str) {m_value = str.c_str();};
  private:
    String m_value;
};

class AsyncWebHeader
{
  public:
    AsyncWebHeader(){};
    const String& value() {return m_value;};
    void SetValue(string str) {m_value = str.c_str();};
  private:
    String m_value;
};

class AsyncWebServerRequest : public http_resource{
  public:
    AsyncWebServerRequest(ArRequestHandlerFunction onRequest);
    const std::shared_ptr<http_response> render(const http_request&) override;
    void send(int status);
    void send(AsyncJsonResponse response);
    void send(AsyncWebServerResponse response);
    void onDisconnect (ArDisconnectHandler fn) {};//TODO
    AsyncWebServerResponse *beginResponse(int code);
    AsyncWebHeader* getHeader(const String& name);
    bool hasParam(const String& name);
    AsyncWebParameter* getParam(const String& name);
  protected:
    shared_ptr<http_response> m_response = nullptr;
  private:
    ArRequestHandlerFunction m_fun = nullptr;
    unique_ptr<AsyncWebServerResponse> m_tmpResponse= nullptr;
    unique_ptr<AsyncWebHeader> m_tmpHeader= nullptr;
    unique_ptr<AsyncWebParameter> m_tmpParam= nullptr;
    map<string, string, http::header_comparator> m_headers;
    map<string, string, http::arg_comparator> m_params;
};


class AsyncWebServerJSONRequest : public AsyncWebServerRequest{
  public:
    AsyncWebServerJSONRequest(ArJsonRequestHandlerFunction onRequest);
    const std::shared_ptr<http_response> render(const http_request&) override;
  private:
    ArJsonRequestHandlerFunction m_JSONfun = nullptr;
};

class AsyncWebHandler
{
  public:
  void setMethod(WebRequestMethodComposite method) {m_allowedMethods = method;};
  void setMaxContentLength(int maxContentLength){};
  WebRequestMethodComposite GetMethod() const {return m_allowedMethods;};
  virtual AsyncWebServerRequest* CreateRequest() = 0;
  const string& GetURI() const { return m_uri;};
  protected:
    string m_uri;
  private:
    WebRequestMethodComposite m_allowedMethods;
};

class AsyncCallbackJsonWebHandler: public AsyncWebHandler
{
  public:
  AsyncCallbackJsonWebHandler(const char* uri, ArJsonRequestHandlerFunction onRequest, size_t maxJsonBufferSize=1024);
  AsyncCallbackJsonWebHandler(const String& uri, ArJsonRequestHandlerFunction onRequest, size_t maxJsonBufferSize=1024);
  ArJsonRequestHandlerFunction GetFun() {return m_JSONfun;};
  AsyncWebServerRequest* CreateRequest() override;
  private:
    ArJsonRequestHandlerFunction m_JSONfun = nullptr;
};

class AsyncWebServer {
public:
    AsyncWebServer();
    AsyncWebServer(unsigned short port);
    void begin();
    void on(const char* uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest);
    AsyncWebHandler& addHandler(AsyncWebHandler* handler);
private:
    const char* getMethodName(WebRequestMethodComposite method);
    
    unique_ptr<webserver> ws = nullptr;
    vector<AsyncWebServerRequest*> m_requestVec;
    unordered_map<string, AsyncWebServerRequest*> m_handlerMap;
};



#endif