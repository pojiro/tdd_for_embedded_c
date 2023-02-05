#include "LightDriver.h"
#include <stdbool.h>
#include <stddef.h>

static LightDriverInterface interface = NULL;

static bool isValid(LightDriver self) { return interface && self; }

void LightDriver_SetInterface(LightDriverInterface i) { interface = i; }
void LightDriver_TurnOn(LightDriver self) {
  if (isValid(self))
    self->vtable->TurnOn(self);
}
void LightDriver_TurnOff(LightDriver self) {
  if (isValid(self))
    self->vtable->TurnOff(self);
}
void LightDriver_Destroy(LightDriver self) {
  if (isValid(self))
    self->vtable->Destroy(self);
}
