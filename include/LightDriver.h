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
  LightDriverType type;
  int id;
} LightDriverStruct;

void LightDriver_SetInterface(LightDriverInterface);
void LightDriver_TurnOn(LightDriver);

#include "LightDriverPrivate.h"

#endif /* __LIGHT_DRIVER_H__ */
