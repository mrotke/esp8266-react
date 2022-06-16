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