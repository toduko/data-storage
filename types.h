#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <math.h>

typedef int32_t S32;
#define S32_SIZE sizeof(S32)
#define S32_MAX (int)(pow((double)2, (double)31) - 1)
#define S32_MIN (int)(pow((double)2, (double)31) * -1)

typedef int16_t S16;
#define S16_SIZE sizeof(S16)
#define S16_MAX (int)(pow((double)2, (double)15) - 1)
#define S16_MIN (int)(pow((double)2, (double)15) * -1)

typedef uint8_t S8;
#define S8_SIZE sizeof(S8)
#define S8_MAX (int)(pow((double)2, (double)7) - 1)
#define S8_MIN (int)(pow((double)2, (double)7) * -1)

typedef uint32_t U32;
typedef uint8_t U8;

#define TYPE_S32 0
#define TYPE_S16 1
#define TYPE_S8 2
#define TYPE_STRING 3
#define TYPE_S32_LIST 4
#define TYPE_S16_LIST 5
#define TYPE_S8_LIST 6
#define TYPE_STRING_LIST 7
#define TYPE_STATIC_STRING 8
#define TYPE_STATIC_S32 9
#define TYPE_STATIC_S16 10
#define TYPE_STATIC_S8 11
#define TYPE_STATIC_S32_MONO 12
#define TYPE_STATIC_S16_MONO 13
#define TYPE_STATIC_S8_MONO 14
#define TYPE_STATIC_STRING_MONO 15

#define MAX_STR_SIZE 256

typedef enum
{
  SUCCESS,
  SAME_VALUE,
  OUT_OF_BOUNDS,
  BUFFER_TOO_SMALL,
  BUFFER_TOO_BIG,
  POINTER_ERROR,
  TYPE_ERROR,
  INT_VALUE_OVERFLOW,
  QUEUE_FULL,
  QUEUE_EMPTY
} DSError;

typedef struct
{
  U8 type;
  union
  {
    void *data;
    const void *const_data;
  };
} DS_DATA;

typedef struct
{
  U8 size;
  S32 *values;
} S32_LIST;

typedef struct
{
  U8 size;
  S16 *values;
} S16_LIST;

typedef struct
{
  U8 size;
  S8 *values;
} S8_LIST;

typedef struct
{
  U8 size;
  char *str;
} String;

typedef struct
{
  U8 size;
  U8 max_str_size;
  char *strings;
} STRING_LIST;

typedef enum
{
  BULGARIAN,
  ENGLISH,
  NUM_LANGUAGES
} Language;

#define Is_WritableInt(element) (element.type == TYPE_S32 || element.type == TYPE_S16 || element.type == TYPE_S8)
#define Is_Not_WritableInt(element) (!Is_WritableInt(element))
#define Is_StaticInt(element) (element.type == TYPE_STATIC_S32 || element.type == TYPE_STATIC_S32_MONO || element.type == TYPE_STATIC_S16 || element.type == TYPE_STATIC_S16_MONO || element.type == TYPE_STATIC_S8 || element.type == TYPE_STATIC_S8_MONO)
#define Is_Not_StaticInt(element) (!Is_StaticInt(element))
#define Is_Int(element) (Is_StaticInt(element) || Is_WritableInt(element))
#define Is_Not_Int(element) (Is_Not_StaticInt(element) && Is_Not_WritableInt(element))
#define Is_String(element) (element.type == TYPE_STRING || element.type == TYPE_STATIC_STRING || element.type == TYPE_STATIC_STRING_MONO)
#define Is_Not_String(element) (!Is_String(element))
#define Is_WritableString(element) (element.type == TYPE_STRING)
#define Is_Not_WritableString(element) (element.type != TYPE_STRING)
#define Is_StaticString(element) (element.type == TYPE_STATIC_STRING || element.type == TYPE_STATIC_STRING_MONO)
#define Is_Not_StaticString(element) (!Is_StaticString(element))
#define Is_IntList(element) (element.type == TYPE_S32_LIST || element.type == TYPE_S16_LIST || element.type == TYPE_S8_LIST)
#define Is_Not_IntList(element) (!Is_IntList(element))
#define Is_StringList(element) (element.type == TYPE_STRING_LIST)
#define Is_Not_StringList(element) (element.type != TYPE_STRING_LIST)

#define Is_Not_In_S16_Bounds(value) (value > S16_MAX || value < S16_MIN)
#define Is_Not_In_S8_Bounds(value) (value > S8_MAX || value < S8_MIN)

#endif
