UNITY_FW_DIR=./unity.framework

CFLAGS  += -I$(UNITY_FW_DIR)/extras/fixture/src \
           -I$(UNITY_FW_DIR)/extras/memory/src  \
           -I$(UNITY_FW_DIR)/src \
           -I./include \
           -I./include/util \
           -I./mocks
LDFLAGS += -L$(UNITY_FW_DIR)/build -lunity

all: build_test
	./run_test

build_test:
	$(CC) -o run_test \
  $(UNITY_FW_DIR)/extras/fixture/src/unity_fixture.c \
  unity/AllTests.c \
  mocks/RuntimeErrorStub.c \
  unity/LedDriver/LedDriverTest.c \
  unity/LedDriver/LedDriverTestRunner.c \
  src/LedDriver.c \
  $(CFLAGS) $(LDFLAGS)
