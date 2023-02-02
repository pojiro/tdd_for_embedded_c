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

  void setTimeTo(Day day, int minuteOfDay) {
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minuteOfDay);
  };

  void checkLightState(int id, int state) {
    LONGS_EQUAL(id, LightControllerSpy_GetLastId());
    LONGS_EQUAL(state, LightControllerSpy_GetLastState());
  }
};

TEST(LightScheduler, NoScheduleNothingHappes) {
  setTimeTo(MONDAY, 10);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayNotTimeYet) {
  LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
  setTimeTo(MONDAY, 1199);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayItsTime) {
  LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
  setTimeTo(MONDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffEverydayItsTime) {
  LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
  setTimeTo(MONDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleTuesdayButMonday) {
  LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
  setTimeTo(MONDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}
