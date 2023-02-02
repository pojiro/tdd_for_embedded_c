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
    if (id == LIGHT_ID_UNKNOWN) {
      LONGS_EQUAL(id, LightControllerSpy_GetLastId());
      LONGS_EQUAL(state, LightControllerSpy_GetLastState());
    } else {
      LONGS_EQUAL(state, LightControllerSpy_GetLightState(id));
    }
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

TEST(LightScheduler, ScheduleTuesdayAndItsTuesday) {
  LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
  setTimeTo(TUESDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndAndItsFriday) {
  LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
  setTimeTo(FRIDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekEndAndItsSaturday) {
  LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
  setTimeTo(SATURDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndAndItsSunday) {
  LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
  setTimeTo(SUNDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndAndItsMonday) {
  LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
  setTimeTo(MONDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleTwoEventsAtTheSameTime) {
  LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
  LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);

  setTimeTo(SUNDAY, 1200);

  LightScheduler_Wakeup();

  checkLightState(3, LIGHT_ON);
  checkLightState(12, LIGHT_ON);
}

TEST(LightScheduler, RejectsTooManyEvents) {
  int i;
  for (i = 0; i < 128; i++) {
    LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(3, SUNDAY, 600 + i));
  }
  LONGS_EQUAL(LS_TOO_MANY_EVENTS,
              LightScheduler_ScheduleTurnOn(3, SUNDAY, 600 + i));
}

TEST_GROUP(LightSchedulerInitAndCleanup){};

TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm) {
  LightScheduler_Create();
  POINTERS_EQUAL((void *)LightScheduler_Wakeup,
                 (void *)FakeTimeService_GetAlarmCallback());

  LONGS_EQUAL(60, FakeTimeService_GetAlarmPeriod());
  LightScheduler_Destroy();
}

TEST(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm) {
  LightScheduler_Create();
  LightScheduler_Destroy();
  POINTERS_EQUAL(NULL, (void *)FakeTimeService_GetAlarmCallback());
}
