#include "ESPAsyncWebServer.h"

AsyncWebServer::AsyncWebServer()
{
    ws = create_webserver(80);
}

AsyncWebServer::AsyncWebServer(uint16_t port)
{
    ws = create_webserver(port);
}

void AsyncWebServer::begin()
{
    ws.start(false);
}

void AsyncWebServer::on(const char* uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest)
{
    AsyncWebServerRequest* req = new AsyncWebServerRequest(onRequest);
    req->disallow_all();
    req->set_allowing(getMethodName(method), true);
    ws.register_resource(uri, req);
    m_requestVec.push_back(req);
}


const char* AsyncWebServer::getMethodName(WebRequestMethodComposite method)
{
    switch(method)
    {
    case WebRequestMethod::HTTP_GET:
        return "GET";
    case WebRequestMethod::HTTP_POST:
        return "POST";
    case WebRequestMethod::HTTP_DELETE:
        return "DELETE";
    case WebRequestMethod::HTTP_ANY:
        return "ANY";
    case WebRequestMethod::HTTP_PUT:
        return "PUT";
    case WebRequestMethod::HTTP_HEAD:
        return "HEAD";
    case WebRequestMethod::HTTP_OPTIONS:
        return "OPTIONS";
    case WebRequestMethod::HTTP_PATCH:
        return "PATCH";
    default:
        return "UNKNOWN";
    }
}

const std::shared_ptr<http_response> AsyncWebServerRequest::render(const http_request&)
{
    return std::shared_ptr<http_response>(new string_response("Hello, World!"));//TODO
}