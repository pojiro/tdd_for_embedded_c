#include "TimeService.h"

void FakeTimeService_SetMinute(int);
void FakeTimeService_SetDay(Day);

WakeupCallback FakeTimeService_GetAlarmCallback(void);
int FakeTimeService_GetAlarmPeriod(void);
