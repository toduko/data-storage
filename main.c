#include "ds_interface.h"

int main()
{
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

  DS_WriteInt(ENGINE, 20);
  DS_ReadInt(ENGINE, &s32Data);
  printf("ENGINE data: %d\n", s32Data);

  return 0;
}
