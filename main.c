#include "ds_interface.h"
#include <stdlib.h>

int main()
{
  system(" ");

  Seed_Data();

  char str[MAX_STR_SIZE];

  DS_ReadString(BRAKE_PEDAL, str, sizeof(str));
  printf("BRAKE_PEDAL data before: %s\n", str);

  DS_WriteString(BRAKE_PEDAL, "BRAKE");
  DS_ReadString(BRAKE_PEDAL, str, sizeof(str));
  printf("BRAKE_PEDAL data after: %s\n", str);

  S32 s32Data;

  printf("CLUTCH data before: %d\n", s32Data);

  DS_WriteInt(CLUTCH, 321);
  DS_ReadInt(CLUTCH, &s32Data);
  printf("CLUTCH data after: %d\n", s32Data);

  DS_ReadInt(GEAR_BOX, &s32Data);
  DS_ReadInt(DATA_SIZE, &s32Data);

  return 0;
}
