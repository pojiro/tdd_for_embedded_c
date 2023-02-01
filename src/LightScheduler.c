#include "LightScheduler.h"
#include "LightController.h"

typedef struct {
  int id;
  int minuteOfDay;
  int event;
} ScheduleLightEvent;

enum { UNUSED = -1 };
enum { TURN_ON, TURN_OFF };

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

  if (scheduledEvent.event == TURN_ON)
    LightController_On(scheduledEvent.id);
  else
    LightController_Off(scheduledEvent.id);
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay) {
  scheduledEvent.id = id;
  scheduledEvent.minuteOfDay = minuteOfDay;
  scheduledEvent.event = TURN_ON;
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay) {
  scheduledEvent.id = id;
  scheduledEvent.minuteOfDay = minuteOfDay;
  scheduledEvent.event = TURN_OFF;
}
