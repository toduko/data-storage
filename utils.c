#include "utils.h"

void Log_Result(const char *name, const DSError status)
{
#ifdef DEBUG
  system(" ");

  char *color;
  char *result;
  switch (status)
  {
  case SUCCESS:
    color = GREEN;
    result = "SUCCESS";
    break;
  case SAME_VALUE:
    color = YELLOW;
    result = "SAME_VALUE";
    break;
  case OUT_OF_BOUNDS:
    color = YELLOW;
    result = "OUT_OF_BOUNDS";
    break;
  case BUFFER_TOO_SMALL:
    color = YELLOW;
    result = "BUFFER_TOO_SMALL";
    break;
  case BUFFER_TOO_BIG:
    color = YELLOW;
    result = "BUFFER_TOO_BIG";
    break;
  case POINTER_ERROR:
    color = RED;
    result = "POINTER_ERROR";
    break;
  case TYPE_ERROR:
    color = RED;
    result = "TYPE_ERROR";
    break;
  case INT_VALUE_OVERFLOW:
    color = RED;
    result = "INT_VALUE_OVERFLOW";
    break;
  case QUEUE_EMPTY:
    color = RED;
    result = "QUEUE_EMPTY";
    break;
  case QUEUE_FULL:
    color = RED;
    result = "QUEUE_FULL";
    break;
  }
  printf("%s result: %s%s%s\n", name, color, result, RESET);
#endif
}

U8 Is_Big_Endian()
{
  unsigned int i = 1;
  char *c = (char *)&i;
  if (*c)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

void S32_To_S8_Array_Lit_End(S32 src, S8 *dest)
{
  dest[0] = (S8)(src >> 0);
  dest[1] = (S8)(src >> 8);
  dest[2] = (S8)(src >> 16);
  dest[3] = (S8)(src >> 24);
}

void S32_To_S16_Array_Lit_End(S32 src, S16 *dest)
{
  dest[0] = (S16)(src >> 0);
  dest[1] = (S16)(src >> 16);
}

S8 S32_To_S8(S32 value)
{
  S8 s8arr[4];
  S32_To_S8_Array_Lit_End(value, s8arr);
  return s8arr[0] | s8arr[3];
}

S32 S8_To_S32(S8 value)
{
  if (Is_Big_Endian())
  {
    return (S32)value << 24;
  }
  else
  {
    return (S32)value << 0;
  }
}

S16 S32_To_S16(S32 value)
{
  S16 s16arr[2];
  S32_To_S16_Array_Lit_End(value, s16arr);

  return s16arr[0] | s16arr[1];
}

S32 S16_To_S32(S16 value)
{
  if (Is_Big_Endian())
  {
    return (S32)value << 16;
  }
  else
  {
    return (S32)value << 0;
  }
}

void sort_relations(Relationship relationships[], int first, int last)
{
  int i, j, pivot;
  Relationship temp;

  if (first < last)
  {
    pivot = first;
    i = first;
    j = last;

    while (i < j)
    {
      while (relationships[i].element <= relationships[pivot].element && i < last)
        i++;
      while (relationships[j].element > relationships[pivot].element)
        j--;
      if (i < j)
      {
        temp = relationships[i];
        relationships[i] = relationships[j];
        relationships[j] = temp;
      }
    }

    temp = relationships[pivot];
    relationships[pivot] = relationships[j];
    relationships[j] = temp;
    sort_relations(relationships, first, j - 1);
    sort_relations(relationships, j + 1, last);
  }
}

int binary_search_element(const Relationship relationships[], int size, DSID value)
{
  int low = 0, high = size - 1, result = -1;

  while (low <= high)
  {
    int mid = (high - low) / 2 + low;
    if (relationships[mid].element > value)
    {
      high = mid - 1;
    }
    else if (relationships[mid].element == value)
    {
      result = mid;
      high = mid - 1;
    }
    else
    {
      low = mid + 1;
    }
  }
  
  return result;
}