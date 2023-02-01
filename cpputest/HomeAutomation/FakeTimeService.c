#include "FakeTimeService.h"

static Time faketime;

void TimeService_Create() {
  faketime.minuteOfDay = -1;
  faketime.dayOfWeek = -1;
}

void TimeService_Destroy() {}

void TimeService_GetTime(Time *time) {
  time->minuteOfDay = faketime.minuteOfDay;
  time->dayOfWeek = faketime.dayOfWeek;
}

void FakeTimeService_SetMinute(int minute) { faketime.minuteOfDay = minute; }
void FakeTimeService_SetDay(Day day) { faketime.dayOfWeek = day; }
