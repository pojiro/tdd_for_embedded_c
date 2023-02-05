#include "LightDriver.h"
#include <stddef.h>

static LightDriverInterface interface = NULL;

void LightDriver_SetInterface(LightDriverInterface i) { interface = i; }
void LightDriver_TurnOn(LightDriver self) { interface->TurnOn(self); }