#ifndef TYPES_H_
#define TYPES_H_
#include <stdint.h>

typedef int32_t S32;
typedef uint32_t U32;
typedef unsigned char UC;

#define MAX_STR_SIZE 256

typedef enum
{
  SUCCESS,
  OUT_OF_BOUNDS,
  POINTER_ERROR,
  BUFFER_TOO_SMALL,
} DSError;

typedef struct
{
  void *data;
} DS_DATA;

#endif