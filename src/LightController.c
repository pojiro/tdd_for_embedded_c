#include "LightController.h"
#include "LightDriverSpy.h"
#include <stdlib.h>
#include <string.h>

static LightDriver lightDrivers[MAX_LIGHTS] = {NULL};

void LightController_Create(void) {
  memset(lightDrivers, 0, sizeof(lightDrivers));
}

void LightController_On(int id) {
  LightDriver driver = lightDrivers[id];
  if (driver == NULL)
    return;

  switch (driver->type) {
  case X10:
    break;
  case AcmeWireless:
    break;
  case MemoryMapped:
    break;
  case TestLightDriver:
    LightDriverSpy_TurnOn(driver);
    break;
  default:
    break;
  }
}

static void destroy(LightDriver driver) {
  if (driver == NULL)
    return;

  switch (driver->type) {
  case X10:
    break;
  case AcmeWireless:
    break;
  case MemoryMapped:
    break;
  case TestLightDriver:
    LightDriverSpy_Destroy(driver);
    break;
  default:
    break;
  }
}

void LightController_Destroy(void) {
  for (int i = 0; i < MAX_LIGHTS; i++) {
    LightDriver driver = lightDrivers[i];
    destroy(driver);
    lightDrivers[i] = NULL;
  }
}

bool LightController_Add(int id, LightDriver driver) {
  if (id < 1 || id >= MAX_LIGHTS)
    return false;

  if (lightDrivers[id] != NULL)
    destroy(lightDrivers[id]);

  lightDrivers[id] = driver;
  return true;
}
