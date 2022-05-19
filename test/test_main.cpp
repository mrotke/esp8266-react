#include <ArduinoFake.h>
#include <unity.h>
#include <LightStateService.h>


using namespace fakeit;

void test_setup(void)
{
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