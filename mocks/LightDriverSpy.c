#include "LightDriverSpy.h"
#include <stdlib.h>

typedef struct LightDriverSpyStruct *LightDriverSpy;
typedef struct LightDriverSpyStruct {
  LightDriverStruct base;
} LightDriverSpyStruct;

static int states[MAX_LIGHTS];
static LightDriverInterfaceStruct interface = {LightDriverSpy_TurnOn};

void LightDriverSpy_Reset(void) {
  for (int i = 0; i < MAX_LIGHTS; i++) {
    states[i] = LIGHT_STATE_UNKNOWN;
  }
}

LightDriver LightDriverSpy_Create(int id) {
  LightDriverSpy self = malloc(sizeof(LightDriverSpyStruct));
  self->base.type = TestLightDriver;
  self->base.id = id;
  return (LightDriver)self;
}

void LightDriverSpy_Destroy(LightDriver super) {
  if (super == NULL)
    return;
  LightDriverSpy self = (LightDriverSpy)super;
  states[self->base.id] = LIGHT_STATE_UNKNOWN;
  free(self);
}

void LightDriverSpy_TurnOn(LightDriver super) {
  LightDriverSpy self = (LightDriverSpy)super;
  states[self->base.id] = LIGHT_ON;
}

int LightDriverSpy_GetState(int id) { return states[id]; }

void LightDriverSpy_AddSpiesToController(void) {
  for (int i = 0; i < MAX_LIGHTS; i++) {
    LightDriver driver = LightDriverSpy_Create(i);
    LightController_Add(i, driver);
  }
}

void LightDriverSpy_InstallInterface(void) {
  LightDriver_SetInterface(&interface);
}
