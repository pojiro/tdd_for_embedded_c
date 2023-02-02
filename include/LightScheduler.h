#include "TimeService.h"

enum { LS_OK, LS_TOO_MANY_EVENTS };

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);

void LightScheduler_Wakeup(void);
int LightScheduler_ScheduleTurnOn(int, Day, int);
int LightScheduler_ScheduleTurnOff(int, Day, int);
