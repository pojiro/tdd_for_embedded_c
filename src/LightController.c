#include "LightController.h"
#include "LightDriverSpy.h"
#include <stdlib.h>
#include <string.h>

static LightDriver lightDrivers[MAX_LIGHTS] = {NULL};

void LightController_Create(void) {
  memset(lightDrivers, 0, sizeof(lightDrivers));
}

void LightController_On(int id) { LightDriver_TurnOn(lightDrivers[id]); }
void LightController_Off(int id) { LightDriver_TurnOff(lightDrivers[id]); }

static void destroy(LightDriver driver) { LightDriver_Destroy(driver); }

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
