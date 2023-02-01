#include "LightScheduler.h"
#include "LightController.h"

typedef struct {
  int id;
  int minuteOfDay;
} ScheduleLightEvent;

enum { UNUSED = -1 };

static ScheduleLightEvent scheduledEvent;

void LightScheduler_Create() { scheduledEvent.id = UNUSED; }
void LightScheduler_Destroy() {}

void LightScheduler_Wakeup() {
  Time time;
  TimeService_GetTime(&time);

  if (scheduledEvent.id == UNUSED)
    return;
  if (time.minuteOfDay != scheduledEvent.minuteOfDay)
    return;

  LightController_On(scheduledEvent.id);
}
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay) {
  scheduledEvent.id = id;
  scheduledEvent.minuteOfDay = minuteOfDay;
}
