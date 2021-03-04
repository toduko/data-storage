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

  system(" ");

  Load_Data();

  char str[13];

  DS_ReadString(BRAKE_PEDAL, str, sizeof(str) - 5);
  printf("BRAKE_PEDAL_Data before: %s\n", str);

  DS_WriteString(BRAKE_PEDAL, "BRAKE v2");
  DS_ReadString(BRAKE_PEDAL, str, sizeof(str));
  printf("BRAKE_PEDAL_Data after: %s\n", str);

  S32 s32Data;

  printf("CLUTCH_Data before: %d\n", s32Data);

  DS_WriteInt(CLUTCH, 321);
  DS_ReadInt(CLUTCH, &s32Data);
  printf("CLUTCH_Data after: %d\n", s32Data);

  DS_ReadInt(ENGINE, &s32Data);
  DS_ReadInt(DATA_SIZE, &s32Data);

  return 0;
}
