#ifndef JsonUtils_h
#define JsonUtils_h

#include <Arduino.h>
#include <IPUtils.h>
#include <ArduinoJson.h>
#include "IPAddress.h"

class JsonUtils {
 public:
  static void readIP(JsonObject& root, const String& key, IPAddress& ip, const String& def) {
    IPAddress defaultIp = {};
    if (!defaultIp.fromString(def)) {
      defaultIp = INADDR_NONE;
    }
    readIP(root, key, ip, defaultIp);
  }
  static void readIP(JsonObject& root, const String& key, IPAddress& ip, const IPAddress& defaultIp = INADDR_NONE) {
    if (!root[key].is<String>() || !ip.fromString(root[key].as<String>())) {
      ip = defaultIp;
    }
  }
  static void writeIP(JsonObject& root, const String& key, const IPAddress& ip) {
    if (IPUtils::isSet(ip)) {
    String sstr;
    sstr.reserve(16); // 4 bytes with 3 chars max + 3 dots + nullterm, or '(IP unset)'
    //sstr += String()

    for (int i =0; i < 3; i++)
    {
        sstr += String(ip[i]);
        sstr += String('.');
    }
    sstr += String(ip[3]);
    root[key] = sstr;
    }
  }
};

#endif  // end JsonUtils
