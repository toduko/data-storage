#ifndef TYPES_H_
#define TYPES_H_

typedef signed int S32;
typedef unsigned int U32;
typedef unsigned char UC;

#define MAX_STR_SIZE 256

typedef enum
{
  SUCCESS,
  OUT_OF_BOUNDS,
  POINTER_ERROR
} DSError;

#endif