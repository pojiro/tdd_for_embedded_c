#include "LightScheduler.h"
#include "LightController.h"

typedef struct {
  int id;
  int minuteOfDay;
  int event;
} ScheduleLightEvent;

enum { UNUSED = -1 };
typedef enum { TURN_ON, TURN_OFF } Event;

static ScheduleLightEvent scheduledEvent;

static void scheduleEvent(int id, Day day, int minuteOfDay, Event event) {
  scheduledEvent.id = id;
  scheduledEvent.minuteOfDay = minuteOfDay;
  scheduledEvent.event = event;
}

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
  scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay) {
  scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}
