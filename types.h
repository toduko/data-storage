#ifndef TYPES_H_
#define TYPES_H_
#include <stdint.h>

typedef int32_t S32;
typedef uint32_t U32;
typedef uint8_t U8;

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
  POINTER_ERROR,
  TYPE_ERROR
} DSError;

enum DS_DATA_TYPES
{
  INT,
  STRING
};

typedef struct
{
  U8 type;
  void *data;
} DS_DATA;

#endif