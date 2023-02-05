#include "CppUTest/TestHarness.h"

extern "C" {
#include "LightDriverSpy.h"
}

TEST_GROUP(LightDriverSpy) {
  LightDriver lightDriverSpy;

  void setup() {
    LightDriverSpy_Reset();
    lightDriverSpy = LightDriverSpy_Create(1);
    LightDriverSpy_InstallInterface();
  };
  void teardown() { LightDriverSpy_Destroy(lightDriverSpy); };
};

TEST(LightDriverSpy, On) {
  LightDriver_TurnOn(lightDriverSpy);
  LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(1));
}
