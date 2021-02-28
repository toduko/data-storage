#include "generated_data.h"

DS_DATA DS_GENERATED_DATA[DATA_SIZE];

S32 CLUTCH_Data;
S32 GEAR_BOX_Data;
char BRAKE_PEDAL_Data[MAX_STR_SIZE] = "BRAKE v1";
char ENGINE_Data[MAX_STR_SIZE] = "ENGINE v1";

void Load_Data()
{
    Set_Location(CLUTCH, &CLUTCH_Data);
    Set_Location(GEAR_BOX, &GEAR_BOX_Data);
    Set_Location(BRAKE_PEDAL, &BRAKE_PEDAL_Data);
    Set_Location(ENGINE, &ENGINE_Data);
}