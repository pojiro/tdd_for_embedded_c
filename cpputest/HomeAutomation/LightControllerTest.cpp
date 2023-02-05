#include "CppUTest/TestHarness.h"

extern "C" {
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
