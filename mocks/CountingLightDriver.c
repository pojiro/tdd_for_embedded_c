#include "CountingLightDriver.h"
#include <stdlib.h>

typedef struct CountingLightDriverStruct *CountingLightDriver;

typedef struct CountingLightDriverStruct {
  LightDriverStruct base;
  int counter;
} CountingLightDriverStruct;

static void count(LightDriver base) {
  CountingLightDriver self = (CountingLightDriver)base;
  self->counter++;
}

LightDriver CountingLightDriver_Create(int id) {
  CountingLightDriver self = malloc(sizeof(CountingLightDriverStruct));
  self->base.type = "CountingLightDriver";
  self->base.id = id;
  return (LightDriver)self;
}

int CountingLightDriver_GetCallCount(LightDriver base) {
  CountingLightDriver self = (CountingLightDriver)base;
  return self->counter;
}
