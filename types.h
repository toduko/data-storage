#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <math.h>
#include "generated_ids.h"

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
#define TYPE_S32_MIN_ID 0
#define TYPE_S32_MAX_ID 1
#define IS_S32(id) (id >= TYPE_S32_MIN_ID && id <= TYPE_S32_MAX_ID)

#define TYPE_S16 1
#define TYPE_S16_MIN_ID 2
#define TYPE_S16_MAX_ID 3
#define IS_S16(id) (id >= TYPE_S16_MIN_ID && id <= TYPE_S16_MAX_ID)

#define TYPE_S8 2
#define TYPE_S8_MIN_ID 4
#define TYPE_S8_MAX_ID 5
#define IS_S8(id) (id >= TYPE_S8_MIN_ID && id <= TYPE_S8_MAX_ID)

#define TYPE_STRING 3
#define TYPE_STRING_MIN_ID 6
#define TYPE_STRING_MAX_ID 7
#define IS_STRING(id) (id >= TYPE_STRING_MIN_ID && id <= TYPE_STRING_MAX_ID)

#define TYPE_S32_LIST 4
#define TYPE_S32_LIST_MIN_ID 8
#define TYPE_S32_LIST_MAX_ID 9
#define IS_S32_LIST(id) (id >= TYPE_S32_LIST_MIN_ID && id <= TYPE_S32_LIST_MAX_ID)

#define TYPE_S16_LIST 5
#define TYPE_S16_LIST_MIN_ID 10
#define TYPE_S16_LIST_MAX_ID 11
#define IS_S16_LIST(id) (id >= TYPE_S16_LIST_MIN_ID && id <= TYPE_S16_LIST_MAX_ID)

#define TYPE_S8_LIST 6
#define TYPE_S8_LIST_MIN_ID 12
#define TYPE_S8_LIST_MAX_ID 13
#define IS_S8_LIST(id) (id >= TYPE_S8_LIST_MIN_ID && id <= TYPE_S8_LIST_MAX_ID)

#define TYPE_STRING_LIST 7
#define TYPE_STRING_LIST_MIN_ID 14
#define TYPE_STRING_LIST_MAX_ID 15
#define IS_STRING_LIST(id) (id >= TYPE_STRING_LIST_MIN_ID && id <= TYPE_STRING_LIST_MAX_ID)

#define TYPE_STATIC_STRING 8
#define TYPE_STATIC_STRING_MIN_ID 16
#define TYPE_STATIC_STRING_MAX_ID 17
#define IS_STATIC_STRING(id) (id >= TYPE_STATIC_STRING_MIN_ID && id <= TYPE_STATIC_STRING_MAX_ID)

#define TYPE_STATIC_S32 9
#define TYPE_STATIC_S32_MIN_ID 18
#define TYPE_STATIC_S32_MAX_ID 19
#define IS_STATIC_S32(id) (id >= TYPE_STATIC_S32_MIN_ID && id <= TYPE_STATIC_S32_MAX_ID)

#define TYPE_STATIC_S16 10
#define TYPE_STATIC_S16_MIN_ID 20
#define TYPE_STATIC_S16_MAX_ID 21
#define IS_STATIC_S16(id) (id >= TYPE_STATIC_S16_MIN_ID && id <= TYPE_STATIC_S16_MAX_ID)

#define TYPE_STATIC_S8 11
#define TYPE_STATIC_S8_MIN_ID 22
#define TYPE_STATIC_S8_MAX_ID 23
#define IS_STATIC_S8(id) (id >= TYPE_STATIC_S8_MIN_ID && id <= TYPE_STATIC_S8_MAX_ID)

#define TYPE_STATIC_S32_MONO 12
#define TYPE_STATIC_S32_MONO_MIN_ID 24
#define TYPE_STATIC_S32_MONO_MAX_ID 25
#define IS_STATIC_S32_MONO(id) (id >= TYPE_STATIC_S32_MONO_MIN_ID && id <= TYPE_STATIC_S32_MONO_MAX_ID)

#define TYPE_STATIC_S16_MONO 13
#define TYPE_STATIC_S16_MONO_MIN_ID 26
#define TYPE_STATIC_S16_MONO_MAX_ID 27
#define IS_STATIC_S16_MONO(id) (id >= TYPE_STATIC_S16_MONO_MIN_ID && id <= TYPE_STATIC_S16_MONO_MAX_ID)

#define TYPE_STATIC_S8_MONO 14
#define TYPE_STATIC_S8_MONO_MIN_ID 28
#define TYPE_STATIC_S8_MONO_MAX_ID 29
#define IS_STATIC_S8_MONO(id) (id >= TYPE_STATIC_S8_MONO_MIN_ID && id <= TYPE_STATIC_S8_MONO_MAX_ID)

#define TYPE_STATIC_STRING_MONO 15
#define TYPE_STATIC_STRING_MONO_MIN_ID 30
#define TYPE_STATIC_STRING_MONO_MAX_ID 31
#define IS_STATIC_STRING_MONO(id) (id >= TYPE_STATIC_STRING_MONO_MIN_ID && id <= TYPE_STATIC_STRING_MONO_MAX_ID)

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

typedef struct
{
  DSID element;
  DSID linkedElement;
} Relationship;

typedef enum
{
  BULGARIAN,
  ENGLISH,
  NUM_LANGUAGES
} Language;

#define Is_WritableInt(id) (id >= TYPE_S32_MIN_ID && id <= TYPE_S8_MAX_ID)
#define Is_Not_WritableInt(id) (!Is_WritableInt(id))
#define Is_StaticInt(id) (IS_STATIC_S32(id) || IS_STATIC_S16(id) || IS_STATIC_S8(id) || IS_STATIC_S32_MONO(id) || IS_STATIC_S16_MONO(id) || IS_STATIC_S8_MONO(id))
#define Is_Not_StaticInt(id) (!Is_StaticInt(id))
#define Is_Int(id) (Is_WritableInt(id) || Is_StaticInt(id))
#define Is_Not_Int(id) (!Is_Int(id))
#define Is_WritableString(id) (id >= TYPE_STRING_MIN_ID && id <= TYPE_STRING_MAX_ID)
#define Is_Not_WritableString(id) (!Is_WritableString(id))
#define Is_StaticString(id) (IS_STATIC_STRING(id) || IS_STATIC_STRING_MONO(id))
#define Is_Not_StaticString(id) (!Is_StaticString(id))
#define Is_String(id) (Is_WritableString(id) || Is_StaticString(id))
#define Is_Not_String(id) (!Is_String(id))
#define Is_IntList(id) (id >= TYPE_S32_LIST_MIN_ID && id <= TYPE_S8_LIST_MAX_ID)
#define Is_Not_IntList(id) (!Is_IntList(id))
#define Is_StringList(id) (id >= TYPE_STRING_LIST_MIN_ID && id <= TYPE_STRING_LIST_MAX_ID)
#define Is_Not_StringList(id) (!Is_StringList(id))

#define Is_Not_In_S16_Bounds(value) (value > S16_MAX || value < S16_MIN)
#define Is_Not_In_S8_Bounds(value) (value > S8_MAX || value < S8_MIN)

#endif
