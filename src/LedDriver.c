#include "LedDriver.h"
#include "RuntimeError.h"
#include <stdbool.h>

enum { ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON };
enum { FIRST_LED = 1, LAST_LED = 16 };

static uint16_t *ledAddress;
static uint16_t ledImage;

static uint16_t convertLedNumberToBit(int ledNumber) {
  return 1 << (ledNumber - 1);
}

static void updateHardware(void) { *ledAddress = ledImage; }

static bool IsLedOutOfBounds(int ledNumber) {
  if ((ledNumber < FIRST_LED) || (ledNumber > LAST_LED)) {
    RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
    return true;
  } else {
    return false;
  }
}

static void setLedImageBit(int ledNumber) {
  ledImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit(int ledNumber) {
  ledImage &= ~(convertLedNumberToBit(ledNumber));
}

void LedDriver_Create(uint16_t *address) {
  ledAddress = address;
  ledImage = ALL_LEDS_OFF;
  updateHardware();
}

void LedDriver_TurnOn(int ledNumber) {
  if (IsLedOutOfBounds(ledNumber))
    return;

  setLedImageBit(ledNumber);
  updateHardware();
}
void LedDriver_TurnOff(int ledNumber) {
  if (IsLedOutOfBounds(ledNumber))
    return;

  clearLedImageBit(ledNumber);
  updateHardware();
}

void LedDriver_TurnAllOn() {
  ledImage = ALL_LEDS_ON;
  updateHardware();
}

void LedDriver_TurnAllOff() {
  ledImage = ALL_LEDS_OFF;
  updateHardware();
}

bool LedDriver_IsOn(int ledNumber) {
  if (IsLedOutOfBounds(ledNumber))
    return false;

  return (ledImage & convertLedNumberToBit(ledNumber)) != 0;
}

bool LedDriver_IsOff(int ledNumber) { return !LedDriver_IsOn(ledNumber); }
