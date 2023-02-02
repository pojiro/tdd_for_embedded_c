#include "LightControllerSpy.h"
#include <stdbool.h>

static int states[32];
static int lastId;
static int lastState;

static bool isIdInRange(int id) { return id >= 0 && id < MAX_LIGHTS; }

void LightController_Create(void) {
  lastId = LIGHT_ID_UNKNOWN;
  lastState = LIGHT_STATE_UNKNOWN;
}

void LightController_Destroy(void) {}

void LightController_On(int id) {
  lastId = id;
  lastState = LIGHT_ON;
  if (isIdInRange(id))
    states[id] = LIGHT_ON;
}

void LightController_Off(int id) {
  lastId = id;
  lastState = LIGHT_OFF;
  if (isIdInRange(id))
    states[id] = LIGHT_OFF;
}

int LightControllerSpy_GetLightState(int id) { return states[id]; }
int LightControllerSpy_GetLastId(void) { return lastId; }
int LightControllerSpy_GetLastState(void) { return lastState; }
