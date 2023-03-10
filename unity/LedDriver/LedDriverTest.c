#include "LedDriver.h"
#include "RuntimeErrorStub.h"
#include "unity_fixture.h"

TEST_GROUP(LedDriver);

static uint16_t virtualLeds;

TEST_SETUP(LedDriver) { LedDriver_Create(&virtualLeds); }
TEST_TEAR_DOWN(LedDriver) {}

TEST(LedDriver, LedsOffAfterCreate) {
  uint16_t virtualLeds = 0xffff;
  LedDriver_Create(&virtualLeds);
  TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne) {
  LedDriver_TurnOn(1);
  TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne) {
  LedDriver_TurnOn(1);
  LedDriver_TurnOff(1);
  TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds) {
  LedDriver_TurnOn(9);
  LedDriver_TurnOn(8);
  TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed) {
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(8);
  TEST_ASSERT_EQUAL_HEX16(0xff7f, virtualLeds);
}

TEST(LedDriver, TurnAllOn) {
  LedDriver_TurnAllOn();
  TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable) {
  virtualLeds = 0xffff;
  LedDriver_TurnOn(8);
  TEST_ASSERT_EQUAL_HEX16(0x0080, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds) {
  LedDriver_TurnOn(1);
  LedDriver_TurnOn(16);
  TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm) {
  LedDriver_TurnOn(-1);
  LedDriver_TurnOn(0);
  LedDriver_TurnOn(17);
  LedDriver_TurnOn(3141);
  TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm) {
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(-1);
  LedDriver_TurnOff(0);
  LedDriver_TurnOff(17);
  LedDriver_TurnOff(3141);
  TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, OutOfBoundsProduceRuntimeError) {
  LedDriver_TurnOn(-1);
  TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED",
                           RuntimeErrorStub_GetLastError());
  TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

TEST(LedDriver, IsOn) {
  TEST_ASSERT_FALSE(LedDriver_IsOn(11));
  LedDriver_TurnOn(11);
  TEST_ASSERT_TRUE(LedDriver_IsOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff) {
  TEST_ASSERT_FALSE(LedDriver_IsOn(0));
  TEST_ASSERT_FALSE(LedDriver_IsOn(17));
  TEST_ASSERT_TRUE(LedDriver_IsOff(0));
  TEST_ASSERT_TRUE(LedDriver_IsOff(17));
}

TEST(LedDriver, IsOff) {
  TEST_ASSERT_TRUE(LedDriver_IsOff(12));
  LedDriver_TurnOn(12);
  TEST_ASSERT_FALSE(LedDriver_IsOff(12));
}

TEST(LedDriver, TurnOffMultipleLeds) {
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(8);
  LedDriver_TurnOff(9);
  TEST_ASSERT_EQUAL_HEX16(0xfe7f, virtualLeds);
}

TEST(LedDriver, TurnAllOff) {
  LedDriver_TurnAllOn();
  LedDriver_TurnAllOff();
  TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
