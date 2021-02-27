#include "ds_interface.h"
#include <stdlib.h>

S32 CLUTCH_Data;
S32 GEAR_BOX_Data;
char BRAKE_PEDAL_Data[MAX_STR_SIZE] = "BRAKE v1";
char ENGINE_Data[MAX_STR_SIZE] = "ENGINE v1";

int Seed_Data()
{
  Set_Location(CLUTCH, &CLUTCH_Data);
  Set_Location(GEAR_BOX, &GEAR_BOX_Data);
  Set_Location(BRAKE_PEDAL, &BRAKE_PEDAL_Data);
  Set_Location(ENGINE, &ENGINE_Data);
}

int main()
{
  system(" ");

  Seed_Data();

  char str[MAX_STR_SIZE];

  DS_ReadString(BRAKE_PEDAL, str, sizeof(str));
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
