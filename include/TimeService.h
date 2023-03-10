#ifndef __TIME_SERVICE_H__
#define __TIME_SERVICE_H__

typedef struct Time {
  int minuteOfDay;
  int dayOfWeek;
} Time;

typedef enum Day {
  EVERYDAY = -3,
  WEEKDAY = -2,
  WEEKEND = -1,
  SUNDAY = 1,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
} Day;

typedef void (*WakeupCallback)(void);

void TimeService_Create(void);
void TimeService_Destroy(void);

void TimeService_GetTime(Time *);

void TimeService_SetPeriodicAlarmInSeconds(int, WakeupCallback);
void TimeService_CancelPeriodicAlarmInSeconds(int, WakeupCallback);

#endif // __TIME_SERVICE_H__
