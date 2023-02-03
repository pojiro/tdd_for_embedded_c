#include "Utils.h"

void FormatOutputSpy_Create(int size);
void FormatOutputSpy_Destroy(void);

int FormatOutputSpy(const char *format, ...);
const char *FormatOutputSpy_GetOutput(void);
