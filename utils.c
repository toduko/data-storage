#include "utils.h"

void Log_Result(const char *name, const DSError status)
{
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
  case POINTER_ERROR:
    color = RED;
    result = "POINTER_ERROR";
    break;
  }
  printf("%s result: %s%s%s\n", name, color, result, RESET);
}