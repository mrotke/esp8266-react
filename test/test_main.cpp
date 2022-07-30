#include <ArduinoFake.h>
#include <unity.h>
#include <LightStateService.h>
#include <ESP8266React.h>

using namespace fakeit;

AsyncWebServer server(80);
//ESP8266React esp8266React(&server);
//LightStateService lightStateService = LightStateService(&server,
//                                                        esp8266React.getSecurityManager());

void test_setup(void)
{
  // start the framework and demo project
  //esp8266React.begin();

  // load the initial light settings
  //lightStateService.begin();
}

void test_loop(void)
{
}

void setUp(void)
{
    ArduinoFakeReset();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_setup);
    RUN_TEST(test_loop);

    UNITY_END();

    return 0;
}