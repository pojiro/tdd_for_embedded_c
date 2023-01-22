#include "LedDriver.h"

enum { ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON };

static uint16_t *ledAddress;
static uint16_t ledImage;

static uint16_t convertLedNumberToBit(int ledNumber) {
  return 1 << (ledNumber - 1);
}

static void updateHardware(void) { *ledAddress = ledImage; }

void LedDriver_Create(uint16_t *address) {
  ledAddress = address;
  ledImage = ALL_LEDS_OFF;
  updateHardware();
}

void LedDriver_TurnOn(int ledNumber) {
  ledImage |= convertLedNumberToBit(ledNumber);
  updateHardware();
}
void LedDriver_TurnOff(int ledNumber) {
  ledImage &= ~(convertLedNumberToBit(ledNumber));
  updateHardware();
}

void LedDriver_TurnAllOn() {
  ledImage = ALL_LEDS_ON;
  updateHardware();
}
