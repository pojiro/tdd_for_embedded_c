#include "RandomMinute.h"
#include <stdlib.h>

static int bound;

void RandomMinute_Create(int b) { bound = b; }
int RandomMinute_Get(void) { return bound - rand() % (bound * 2 + 1); }
