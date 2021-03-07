#include "ds_interface.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    if (strcmp(argv[1], "-d") == 0)
    {
      printf("DEBUG MODE ENABLED\n");
      DEBUG = true;
    }
  }

  Load_Data();

  while (true)
  {
    /*Main loop where data is interacted with*/
    break;
  }

  return 0;
}
