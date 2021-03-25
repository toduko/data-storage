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
  }
  printf("%s result: %s%s%s\n", name, color, result, RESET);
#endif
}

void S32_To_S8_Lit_End(S32 src, S8 *dest)
{
  dest[0] = (S8)(src >> 0);
  dest[1] = (S8)(src >> 8);
  dest[2] = (S8)(src >> 16);
  dest[3] = (S8)(src >> 24);
}

S32 S8_To_S32_Lit_End(S8 *src)
{
  return (S32)src[0] << 0 | (S32)src[1] << 8 | (S32)src[2] << 16 | (S32)src[3] << 24;
}

void S32_To_S16_Lit_End(S32 src, S16 *dest)
{
  dest[0] = (S16)(src >> 0);
  dest[1] = (S16)(src >> 16);
}

S16 S16_To_S32_Lit_End(S16 *src)
{
  return (S32)src[0] << 0 | (S32)src[1] << 16;
}

U8 Is_Big_Endian()
{
  unsigned int i = 1;
  char *c = (char*)&i;
  if (*c)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
