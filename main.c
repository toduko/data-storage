#include "ds_interface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
#ifdef DEBUG
  printf("DEBUG ENABLED\n");
#endif
#include "generated_data.h"
  int i;
  for (i = 0; i < NUM_RELATIONS; ++i)
  {
    printf("%d %d\n", dynamic_relationships[i].element, dynamic_relationships[i].linkedElement);
  }
  while (1)
  {
    /*Main loop where data is interacted with*/
    break;
  }

  return 0;
}
