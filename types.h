#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

typedef int32_t S32;
#define S32_SIZE sizeof(S32)
typedef int16_t S16;
#define S16_SIZE sizeof(S16)
typedef uint8_t S8;
#define S8_SIZE sizeof(S8)
typedef uint32_t U32;
typedef uint8_t U8;

#define INT 0
#define STRING 1

#define MAX_STR_SIZE 256

typedef enum
{
  SUCCESS,
  OUT_OF_BOUNDS,
  BUFFER_TOO_SMALL,
  BUFFER_TOO_BIG,
  POINTER_ERROR,
  TYPE_ERROR
} DSError;

typedef struct
{
  U8 type;
  U8 size;
  void *data;
} DS_DATA;

#endif
