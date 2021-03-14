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
  case INT_SIZE_ERROR:
    color = RED;
    result = "INT_SIZE_ERROR";
    break;
  }
  printf("%s result: %s%s%s\n", name, color, result, RESET);
#endif
}