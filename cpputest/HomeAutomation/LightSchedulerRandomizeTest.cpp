#include "CppUTest/TestHarness.h"

extern "C" {
#include "FakeRandomMinute.h"
#include "FakeTimeService.h"
#include "LightControllerSpy.h"
#include "LightScheduler.h"
}

TEST_GROUP(LightSchedulerRandomize) {
  void setup() {
    LightController_Create();
    LightScheduler_Create();
    UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
  };

  void teardown() {
    LightScheduler_Destroy();
    LightController_Destroy();
  };

  void setTimeTo(Day day, int minuteOfDay) {
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minuteOfDay);
  };

  void checkLightState(int id, int state) {
    if (id == LIGHT_ID_UNKNOWN) {
      LONGS_EQUAL(id, LightControllerSpy_GetLastId());
      LONGS_EQUAL(state, LightControllerSpy_GetLastState());
    } else {
      LONGS_EQUAL(state, LightControllerSpy_GetLightState(id));
    }
  }
};

TEST(LightSchedulerRandomize, TurnsOnEarly) {
  FakeRandomMinute_SetFirstAndIncrement(-10, 5);
  LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
  LightScheduler_Randomize(4, EVERYDAY, 600);
  setTimeTo(MONDAY, 600 - 10);
  LightScheduler_Wakeup();
  checkLightState(4, LIGHT_ON);
}
