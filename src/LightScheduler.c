#include "LightScheduler.h"
#include "LightController.h"
#include <stdbool.h>

typedef struct {
  int id;
  int dayOfWeek;
  int minuteOfDay;
  int event;
} ScheduleLightEvent;

enum { UNUSED = -1 };
enum { MAX_EVENTS = 128 };

typedef enum { TURN_ON, TURN_OFF } Event;

static ScheduleLightEvent scheduledEvents[MAX_EVENTS];

static void scheduleEvent(int id, Day dayOfWeek, int minuteOfDay, Event event) {
  for (int i = 0; i < MAX_EVENTS; i++) {
    if (scheduledEvents[i].id == UNUSED) {
      scheduledEvents[i].id = id;
      scheduledEvents[i].dayOfWeek = dayOfWeek;
      scheduledEvents[i].minuteOfDay = minuteOfDay;
      scheduledEvents[i].event = event;
      break;
    }
  }
}

static void operateLight(ScheduleLightEvent *lightEvent) {
  if (lightEvent->event == TURN_ON)
    LightController_On(lightEvent->id);
  else
    LightController_Off(lightEvent->id);
}

static bool DoesLightRespondToday(Time *time, int reactionDay) {
  int today = time->dayOfWeek;

  if (reactionDay == EVERYDAY)
    return true;
  if (reactionDay == today)
    return true;
  if (reactionDay == WEEKEND && (today == SATURDAY || today == SUNDAY))
    return true;
  if (reactionDay == WEEKDAY && today >= MONDAY && today <= FRIDAY)
    return true;

  return false;
}

static void processEventDueNow(Time *time, ScheduleLightEvent *lightEvent) {
  if (lightEvent->id == UNUSED)
    return;
  if (!DoesLightRespondToday(time, lightEvent->dayOfWeek))
    return;
  if (time->minuteOfDay != lightEvent->minuteOfDay)
    return;
  operateLight(lightEvent);
}

void LightScheduler_Create() {
  for (int i = 0; i < MAX_EVENTS; i++) {
    scheduledEvents[i].id = UNUSED;
  }

  TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}
void LightScheduler_Destroy() {
  TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

void LightScheduler_Wakeup() {
  Time time;
  TimeService_GetTime(&time);

  for (int i = 0; i < MAX_EVENTS; i++) {
    processEventDueNow(&time, &scheduledEvents[i]);
  }
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay) {
  scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay) {
  scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}
