#include "CppUTest/TestHarness.h"

extern "C" {
#include "FakeTimeService.h"
#include "LightControllerSpy.h"
#include "LightScheduler.h"
}

TEST_GROUP(LightScheduler) {
  void setup() {
    LightController_Create();
    LightScheduler_Create();
  };

  void teardown() {
    LightScheduler_Destroy();
    LightController_Destroy();
  };
};

TEST(LightScheduler, NoScheduleNothingHappes) {
  FakeTimeService_SetDay(MONDAY);
  FakeTimeService_SetMinute(10);
  LightScheduler_Wakeup();
  LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
  LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
