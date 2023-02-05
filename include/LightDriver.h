#ifndef __LIGHT_DRIVER_H__
#define __LIGHT_DRIVER_H__

typedef struct LightDriverStruct *LightDriver;
typedef struct LightDriverInterfaceStruct *LightDriverInterface;

typedef enum LightDriverType {
  TestLightDriver,
  X10,
  AcmeWireless,
  MemoryMapped
} LightDriverType;

typedef struct LightDriverStruct {
  const char *type;
  int id;
} LightDriverStruct;

void LightDriver_SetInterface(LightDriverInterface);
void LightDriver_TurnOn(LightDriver);
void LightDriver_TurnOff(LightDriver);
void LightDriver_Destroy(LightDriver);

#include "LightDriverPrivate.h"

#endif /* __LIGHT_DRIVER_H__ */
