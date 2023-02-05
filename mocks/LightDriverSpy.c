#include "LightDriverSpy.h"
#include <stdlib.h>

typedef struct LightDriverSpyStruct *LightDriverSpy;
typedef struct LightDriverSpyStruct {
  LightDriverStruct base;
} LightDriverSpyStruct;

static int states[MAX_LIGHTS];
static void turnOn(LightDriver);
static void turnOff(LightDriver);
static void destroy(LightDriver);
static LightDriverInterfaceStruct interface = {turnOn, turnOff, destroy};

void LightDriverSpy_Reset(void) {
  for (int i = 0; i < MAX_LIGHTS; i++) {
    states[i] = LIGHT_STATE_UNKNOWN;
  }
}

LightDriver LightDriverSpy_Create(int id) {
  LightDriverSpy self = malloc(sizeof(LightDriverSpyStruct));
  self->base.vtable = &interface;
  self->base.type = "TestLightDriver";
  self->base.id = id;
  return (LightDriver)self;
}

static void destroy(LightDriver super) {
  if (super == NULL)
    return;
  LightDriverSpy self = (LightDriverSpy)super;
  states[self->base.id] = LIGHT_STATE_UNKNOWN;
  free(self);
}

static void turnOn(LightDriver super) {
  LightDriverSpy self = (LightDriverSpy)super;
  states[self->base.id] = LIGHT_ON;
}

static void turnOff(LightDriver super) {
  LightDriverSpy self = (LightDriverSpy)super;
  states[self->base.id] = LIGHT_OFF;
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
