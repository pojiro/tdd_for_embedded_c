#include "FakeTimeService.h"
#include <stddef.h>

static Time faketime;
static WakeupCallback callback;
static int period;

void TimeService_Create() {
  faketime.minuteOfDay = -1;
  faketime.dayOfWeek = -1;
}

void TimeService_Destroy() {}

void TimeService_GetTime(Time *time) {
  time->minuteOfDay = faketime.minuteOfDay;
  time->dayOfWeek = faketime.dayOfWeek;
}
void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback cb) {
  period = seconds;
  callback = cb;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback cb) {
  if (period == seconds && callback == cb) {
    period = 0;
    callback = NULL;
  }
}
void FakeTimeService_SetMinute(int minute) { faketime.minuteOfDay = minute; }
void FakeTimeService_SetDay(Day day) { faketime.dayOfWeek = day; }
WakeupCallback FakeTimeService_GetAlarmCallback(void) { return callback; }
int FakeTimeService_GetAlarmPeriod(void) { return period; }
