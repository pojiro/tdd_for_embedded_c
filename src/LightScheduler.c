#include "LightScheduler.h"
#include "LightController.h"

typedef struct {
  int id;
  int day;
  int minuteOfDay;
  int event;
} ScheduleLightEvent;

enum { UNUSED = -1 };
typedef enum { TURN_ON, TURN_OFF } Event;

static ScheduleLightEvent scheduledEvent;

static void scheduleEvent(int id, Day day, int minuteOfDay, Event event) {
  scheduledEvent.id = id;
  scheduledEvent.day = day;
  scheduledEvent.minuteOfDay = minuteOfDay;
  scheduledEvent.event = event;
}

static void operateLight(ScheduleLightEvent *lightEvent) {
  if (lightEvent->event == TURN_ON)
    LightController_On(lightEvent->id);
  else
    LightController_Off(lightEvent->id);
}

static void processEventDueNow(Time *time, ScheduleLightEvent *lightEvent) {
  if (lightEvent->id == UNUSED)
    return;
  if (lightEvent->day != EVERYDAY)
    return;
  if (time->minuteOfDay != lightEvent->minuteOfDay)
    return;
  operateLight(&scheduledEvent);
}

void LightScheduler_Create() { scheduledEvent.id = UNUSED; }
void LightScheduler_Destroy() {}

void LightScheduler_Wakeup() {
  Time time;
  TimeService_GetTime(&time);

  processEventDueNow(&time, &scheduledEvent);
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay) {
  scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay) {
  scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}
