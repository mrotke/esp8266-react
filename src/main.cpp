 #include <ESP8266React.h>
 #include <LightMqttSettingsService.h>
 #include <LightStateService.h>
 #include "Drivers/DriverManager.h"
 #include "Drivers/DriversFactory.h"

#define SERIAL_BAUD_RATE 115200

#ifndef LINUX
AsyncWebServer server(80);
#endif

#ifdef LINUX
AsyncWebServer server(8080);
#endif

ESP8266React esp8266React(&server);
std::shared_ptr<DriverManager> drvManager= std::make_shared<DriverManager>(&server, esp8266React.getFS(),esp8266React.getSecurityManager());

#ifndef LINUX
LightMqttSettingsService lightMqttSettingsService =
    LightMqttSettingsService(&server, esp8266React.getFS(), esp8266React.getSecurityManager());
#endif
LightStateService lightStateService = LightStateService(&server,
                                                        esp8266React.getSecurityManager()
                                                        #ifndef LINUX
                                                        ,
                                                        esp8266React.getMqttClient(),
                                                        &lightMqttSettingsService
                                                        #endif
                                                        );
//DriverGpio driverGpio(&server, esp8266React.getFS(), 1);
void setup() {
#ifndef LINUX
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);
#endif
  DriverManager::CreateInstance(drvManager);
  DriverManager::GetInstance()->Begin();
  // start the framework and demo project
  esp8266React.begin();

  // load the initial light settings
  lightStateService.begin();
#ifndef LINUX
  // start the light service
  lightMqttSettingsService.begin();
#endif
  // start the server
  server.begin();
}

void loop() {
  // run the framework's loop function
  esp8266React.loop();
}

#ifdef LINUX
int main()
{
  setup();

  while (true)
    loop();
  return 0;
}
#endif
