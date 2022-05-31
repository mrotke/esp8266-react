#include <functional>
#include <ArduinoJson.h>

class AsyncWebServer {
};

class AsyncWebServerRequest {
};

/*
 * FILTER :: Callback to filter AsyncWebRewrite and AsyncWebHandler (done by the Server)
 * */

typedef std::function<bool(AsyncWebServerRequest *request)> ArRequestFilterFunction;
typedef std::function<void(AsyncWebServerRequest *request, JsonVariant &json)> ArJsonRequestHandlerFunction;
typedef std::function<void(AsyncWebServerRequest *request)> ArRequestHandlerFunction;