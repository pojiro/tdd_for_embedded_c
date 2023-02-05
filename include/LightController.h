#ifndef __LIGHT_CONTROLLER_H__
#define __LIGHT_CONTROLLER_H__

#include "LightDriver.h"
#include <stdbool.h>

enum { MAX_LIGHTS = 32 };

void LightController_Create(void);
void LightController_Destroy(void);
bool LightController_Add(int id, LightDriver);
void LightController_On(int id);
void LightController_Off(int id);

#endif /* __LIGHT_CONTROLLER_H__ */
