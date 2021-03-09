#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

typedef int32_t S32;
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
  void *data;
} DS_DATA;

typedef struct
{
  U8 size;
  char str[];
} String;

#endif