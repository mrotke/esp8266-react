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

void AsyncWebServerRequest::onDisconnect (ArDisconnectHandler fn)
{
	m_funDisc = fn;
}

void AsyncWebServer::on(const char* uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest)
{
    bool requestExist = false;
    AsyncWebServerJSONRequest* req = nullptr;
    if (m_handlerMap.count(string(uri)))
    {
        req = m_handlerMap[string(uri)];
        requestExist = true;
    }
    else
    {
        req = new AsyncWebServerJSONRequest();
    }
    
    if (!requestExist)
        req->disallow_all();
    
    for (uint8_t i = 0; i < 8 ; i++)
    {
        uint8_t one_method = method & (1 << i);
        if (one_method)
            req->set_allowing(getMethodName(one_method), true);
    }

    if(method == HTTP_GET)
        req->SetGETCallback(onRequest);

    if(method == HTTP_POST)
        req->SetPOSTCallback(onRequest);
    
    if (!requestExist)
    {
        m_handlerMap[string(uri)] = req;
        m_requestVec.push_back(req);
    }

}


AsyncWebHandler& AsyncWebServer::addHandler(AsyncWebHandler* handler)
{
    bool requestExist = false;

    AsyncWebServerJSONRequest* req = nullptr;
    if (m_handlerMap.count(handler->GetURI()))
    {
        req = m_handlerMap[handler->GetURI()];
        requestExist = true;
    }
    else
    {
        req = handler->CreateRequest();
    }

    if (!requestExist)
        req->disallow_all();

    for (uint8_t i = 0; i < 8 ; i++)
    {
        uint8_t one_method = handler->GetMethod() & (1 << i);
        if (one_method)
            req->set_allowing(getMethodName(one_method), true);
    }

    if(handler->GetMethod() == HTTP_GET)
        req->SetGETJSONCallback(handler->GetFun());

    if(handler->GetMethod() == HTTP_POST)
        req->SetPOSTJSONCallback(handler->GetFun());

    if (!requestExist)
    {
        m_handlerMap[handler->GetURI()] = req;
        m_requestVec.push_back(req);
    }


    return *handler;
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

const std::shared_ptr<http_response> AsyncWebServerRequest::render_GET(const http_request& req)
{
    m_headers = req.get_headers();
    m_params = req.get_args();
    m_funGET(this);
    return m_response;
}

const std::shared_ptr<http_response> AsyncWebServerRequest::render_POST(const http_request& req)
{
    m_headers = req.get_headers();
    m_params = req.get_args();
    m_funPOST(this);
    if (m_funDisc)
    	m_funDisc();
    return m_response;
}


AsyncWebServerJSONRequest::AsyncWebServerJSONRequest()
:AsyncWebServerRequest()
{

}

const std::shared_ptr<http_response> AsyncWebServerJSONRequest::render_GET(const http_request& req)
{
    m_headers = req.get_headers();
    m_params = req.get_args();
    if (m_JSONfunGET)
    {
        string content = req.get_content();
        DynamicJsonDocument doc(content.length() + 1);

        deserializeJson(doc , content.c_str());

        JsonVariant variant = doc.as<JsonVariant>();
        m_JSONfunGET(this, variant);
    }
    else if (m_funGET)
    {
        m_funGET(this);
    }


    return m_response;
}

const std::shared_ptr<http_response> AsyncWebServerJSONRequest::render_POST(const http_request& req)
{
    m_headers = req.get_headers();
    m_params = req.get_args();
    if (m_JSONfunPOST)
    {
        String content = String(req.get_content().c_str());
        DynamicJsonDocument doc(1024);

        deserializeJson(doc , content);

        JsonVariant variant = doc.as<JsonVariant>();
        m_JSONfunPOST(this, variant);
    }
    else if (m_funPOST)
    {
        m_funPOST(this);
    }

    if (m_funDisc)
    	m_funDisc();

    return m_response;
}

AsyncJsonResponse::AsyncJsonResponse(bool isArray, size_t maxJsonBufferSize):
m_JSONBuffer(maxJsonBufferSize)
{
      m_code = 200;
      m_contentType = "application/json";
      if(isArray)
        m_root = m_JSONBuffer.createNestedArray();
      else
        m_root = m_JSONBuffer.createNestedObject();
}

const string AsyncJsonResponse::GetContent() const
{
    string str;

    serializeJson(m_root, str);

    return str;
}


AsyncWebServerRequest::AsyncWebServerRequest()
{

}


void AsyncWebServerRequest::send(int status)
{
    m_response =shared_ptr<http_response>(new string_response("", status));
}

void AsyncWebServerRequest::send(AsyncJsonResponse* response)
{
    m_response =shared_ptr<http_response>(new string_response(response->GetContent(), response->GetCode(), response->GetContentType()));
}

void AsyncWebServerRequest::send(AsyncWebServerResponse* response)
{
    m_response =shared_ptr<http_response>(new string_response(response->GetContent(), response->GetCode(), response->GetContentType()));
}

AsyncWebServerResponse* AsyncWebServerRequest::beginResponse(int code)
{
    m_tmpResponse = unique_ptr<AsyncWebServerResponse>(new AsyncWebServerResponse(code));
    return m_tmpResponse.get();
}


AsyncWebHeader* AsyncWebServerRequest::getHeader(const String& name)
{
    if (m_headers.count(string(name.c_str())))
    {
        m_tmpHeader = unique_ptr<AsyncWebHeader>(new AsyncWebHeader());
        m_tmpHeader->SetValue(m_headers[string(name.c_str())]);
        return m_tmpHeader.get();
    }
    else
        return nullptr;
}

AsyncWebParameter* AsyncWebServerRequest::getParam(const String& name)
{
    if (m_params.count(string(name.c_str())))
    {
        m_tmpParam = unique_ptr<AsyncWebParameter>(new AsyncWebParameter());
        m_tmpParam->SetValue(m_headers[string(name.c_str())]);
        return m_tmpParam.get();
    }
    else
        return nullptr;
}

bool AsyncWebServerRequest::hasParam(const String& name)
{
    if (m_params.count(string(name.c_str())))
    {
        return true;
    }
    return false;
}

AsyncCallbackJsonWebHandler::AsyncCallbackJsonWebHandler(const char* uri, ArJsonRequestHandlerFunction onRequest, size_t maxJsonBufferSize)
{
    m_uri = string(uri);
    m_JSONfun = onRequest;
}

AsyncCallbackJsonWebHandler::AsyncCallbackJsonWebHandler(const String& uri, ArJsonRequestHandlerFunction onRequest, size_t maxJsonBufferSize)
{
    m_uri = string(uri.c_str());
    m_JSONfun = onRequest;
}

AsyncWebServerJSONRequest* AsyncCallbackJsonWebHandler::CreateRequest()
{
    AsyncWebServerJSONRequest* request = new AsyncWebServerJSONRequest();

    if (m_allowedMethods == HTTP_GET)
        request->SetGETJSONCallback(m_JSONfun);

    if (m_allowedMethods == HTTP_POST)
        request->SetPOSTJSONCallback(m_JSONfun);

    return request;
}
