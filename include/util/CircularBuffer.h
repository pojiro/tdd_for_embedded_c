typedef struct CircularBufferStruct *CircularBuffer;

CircularBuffer CircularBuffer_Create(int size);
void CircularBuffer_Destroy(CircularBuffer buffer);
void CircularBuffer_Put(CircularBuffer buffer, int value);
int CircularBuffer_Get(CircularBuffer buffer);
void CircularBuffer_Print(CircularBuffer buffer);
