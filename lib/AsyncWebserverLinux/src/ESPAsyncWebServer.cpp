#include "ESPAsyncWebServer.h"
#include <iostream>
#include <stdexcept>

AsyncWebServer::AsyncWebServer()
{
    ws = unique_ptr<webserver>(new webserver(create_webserver(80)));
}

AsyncWebServer::AsyncWebServer(unsigned short port)
{
    ws = unique_ptr<webserver>(new webserver(create_webserver(port)));
}

void AsyncWebServer::begin()
{
    for (auto i : m_handlerMap)
        ws->register_resource(i.first, i.second);
    try 
    {
        ws->start(false);
    } catch (std::invalid_argument const& ex )
    {
        std::cout << "#1: " << ex.what() << '\n';
    }
    
}

void AsyncWebServer::on(const char* uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest)
{
    AsyncWebServerRequest* req = new AsyncWebServerRequest(onRequest);
    req->disallow_all();
    req->set_allowing(getMethodName(method), true);
    //ws.register_resource(uri, req);
    m_handlerMap[string(uri)] = req;
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