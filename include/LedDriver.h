#include <stdbool.h>
#include <stdint.h>

void LedDriver_Create(uint16_t *);
void LedDriver_TurnOn(int);
void LedDriver_TurnOff(int);
void LedDriver_TurnAllOn();
void LedDriver_TurnAllOff();
bool LedDriver_IsOn(int);
bool LedDriver_IsOff(int);
