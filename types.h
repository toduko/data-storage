#ifndef TYPES_H_
#define TYPES_H_
#include <stdint.h>

typedef int32_t S32;
typedef uint32_t U32;
typedef unsigned char UC;
typedef enum
{
  false,
  true
} bool;

#define MAX_STR_SIZE 256

typedef enum
{
  SUCCESS,
  OUT_OF_BOUNDS,
  BUFFER_TOO_SMALL,
  BUFFER_TOO_BIG,
  POINTER_ERROR
} DSError;

typedef struct
{
  void *data;
} DS_DATA;

#endif