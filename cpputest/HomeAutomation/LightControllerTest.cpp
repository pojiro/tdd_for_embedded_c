#include "CppUTest/TestHarness.h"

extern "C" {
#include "CountingLightDriver.h"
#include "LightController.h"
#include "LightDriverSpy.h"
}

TEST_GROUP(LightController) {
  LightDriver spy;
  void setup() {
    LightController_Create();
    // ライト ID 毎にスパイを投入する
    LightDriverSpy_AddSpiesToController();
    LightDriverSpy_InstallInterface();
    LightDriverSpy_Reset();
  }
  void teardown() { LightController_Destroy(); }
};

TEST(LightController, On) {
  LightController_On(7);
  LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(7));
}

TEST(LightController, AddingDriverDestroysPrevious) {
  LightDriver spy = LightDriverSpy_Create(1);
  LightController_Add(1, spy);
  LightController_Destroy();
}

TEST(LightController, TurnOnDiffrentDriversTypes) {
  LightDriver otherDriver = CountingLightDriver_Create(5);
  LightController_Add(5, otherDriver);
  LightController_On(7);
  LightController_On(5);
  LightController_Off(5);

  LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(7));
  LONGS_EQUAL(2, CountingLightDriver_GetCallCount(otherDriver));
}
