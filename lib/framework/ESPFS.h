#ifdef ESP32
#include <SPIFFS.h>
#define ESPFS SPIFFS
#elif defined(ESP8266)
#include <LittleFS.h>
#define ESPFS LittleFS
#elif defined(LINUX)
#include <FS.h>
#define ESPFS linuxFS
#endif
