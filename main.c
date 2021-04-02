#include "ds_interface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
#ifdef DEBUG
  printf("DEBUG ENABLED\n");
#endif
  char str[MAX_STR_SIZE];
  DS_ReadString(SPEED, str, sizeof(str));
  printf("%s\n", str);
  while (1)
  {
    /*Main loop where data is interacted with*/
    break;
  }

  return 0;
}
