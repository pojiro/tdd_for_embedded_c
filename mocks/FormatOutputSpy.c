#include "FormatOutputSpy.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static char *buffer = NULL;
static size_t buffer_size = 0;
static int buffer_offset = 0;

void FormatOutputSpy_Create(int size) {
  FormatOutputSpy_Destroy();
  buffer_size = size + 1;
  buffer = (char *)malloc(buffer_size);
  buffer_offset = 0;
  buffer[0] = '\0';
}
void FormatOutputSpy_Destroy(void) {
  if (buffer == NULL)
    return;
  free(buffer);
  buffer = NULL;
}

int FormatOutputSpy(const char *format, ...) {
  va_list args;
  va_start(args, format);
  int written_size = vsnprintf(buffer + buffer_offset,
                               buffer_size - buffer_offset, format, args);
  buffer_offset += written_size;
  va_end(args);

  return written_size;
}
const char *FormatOutputSpy_GetOutput(void) { return buffer; }
