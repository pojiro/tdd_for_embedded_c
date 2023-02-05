#include "CppUTest/TestHarness.h"

extern "C" {
#include "LightDriver.h"
}

#define NONSENSE_POINTER (LightDriver) ~0
static LightDriver savedDriver = NONSENSE_POINTER;
static void shouldNotBeCalled(LightDriver self) { savedDriver = self; }

LightDriverInterfaceStruct interface = {shouldNotBeCalled, shouldNotBeCalled,
                                        shouldNotBeCalled};

LightDriverStruct testDriver = {TestLightDriver, 13};

TEST_GROUP(LightDriver){};

TEST(LightDriver, NullDeviceDoesNotCrash) {
  LightDriver_SetInterface(&interface);
  LightDriver_TurnOn(NULL);
  LightDriver_TurnOff(NULL);
  LightDriver_Destroy(NULL);
  POINTERS_EQUAL(NONSENSE_POINTER, savedDriver);
}

TEST(LightDriver, NullInterfaceDoesNotCrash) {
  LightDriver_SetInterface(NULL);
  LightDriver_TurnOn(&testDriver);
  LightDriver_TurnOff(&testDriver);
  LightDriver_Destroy(&testDriver);
  POINTERS_EQUAL(NONSENSE_POINTER, savedDriver);
}
