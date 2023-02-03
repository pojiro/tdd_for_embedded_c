#include "CircularBuffer.h"
#include "Utils.h"
#include <stdlib.h>

typedef struct CircularBufferStruct {
  int *values;
  int in_index;
  int out_index;
  int count;
  int capacity;
} CircularBufferStruct;

CircularBuffer CircularBuffer_Create(int size) {
  CircularBuffer buffer = (CircularBuffer)malloc(sizeof(CircularBufferStruct));
  buffer->values = (int *)malloc(sizeof(int) * size);
  buffer->in_index = 0;
  buffer->out_index = 0;
  buffer->count = 0;
  buffer->capacity = size;
  return buffer;
}

void CircularBuffer_Destroy(CircularBuffer buffer) {
  if (buffer->values != NULL)
    free(buffer->values);
  if (buffer != NULL)
    free(buffer);
}

int CircularBuffer_Get(CircularBuffer buffer) {
  int value = buffer->values[buffer->out_index++];
  buffer->count -= 1;

  if (buffer->out_index == buffer->capacity)
    buffer->out_index = 0;

  return value;
}

void CircularBuffer_Put(CircularBuffer buffer, int value) {
  buffer->values[buffer->in_index++] = value;
  buffer->count += 1;

  if (buffer->in_index == buffer->capacity)
    buffer->in_index = 0;
}

void CircularBuffer_Print(CircularBuffer buffer) {
  int index = buffer->out_index;

  FormatOutput("Circular buffer contest:\n<");
  for (int i = 0; i < buffer->count; i++) {
    if (i != 0)
      FormatOutput(", ");
    FormatOutput("%d", buffer->values[index++]);
    if (index == buffer->capacity)
      index = 0;
  }
  FormatOutput(">\n");
}
