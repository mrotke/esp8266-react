#include <SettingValue.h>

namespace SettingValue {

#ifdef ESP32
const String PLATFORM = "esp32";
#elif defined(ESP8266)
const String PLATFORM = "esp8266";
#elif defined(LINUX)
const String PLATFORM = "LINUX";
#endif

/**
 * Returns a new string after replacing each instance of the pattern with a value generated by calling the provided
 * callback.
 */
String replaceEach(String value, String pattern, String (*generateReplacement)()) {
  while (true) {
    int index = value.indexOf(pattern);
    if (index == -1) {
      break;
    }
    value = value.substring(0, index) + generateReplacement() + value.substring(index + pattern.length());
  }
  return value;
}

/**
 * Generates a random number, encoded as a hex string.
 */
String getRandom() {
  #ifdef LINUX
  return String(rand()%2147483647,HEX);
  #else
  return String(random(2147483647), HEX);
  #endif
}

/**
 * Uses the station's MAC address to create a unique id for each device.
 */
String getUniqueId() {
  uint8_t mac[6];
#ifdef ESP32
  esp_read_mac(mac, ESP_MAC_WIFI_STA);
#elif defined(ESP8266)
  wifi_get_macaddr(STATION_IF, mac);
#endif
  char macStr[13] = {0};
  sprintf(macStr, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(macStr);
}

String format(String value) {
  value = replaceEach(value, "#{random}", getRandom);
  value.replace("#{unique_id}", getUniqueId());
  value.replace("#{platform}", PLATFORM);
  return value;
}

};  // end namespace SettingValue
