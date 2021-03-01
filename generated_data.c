#include "generated_data.h"

S32 CLUTCH_Data;
S32 GEAR_BOX_Data;
char BRAKE_PEDAL_Data[MAX_STR_SIZE] = "BRAKE v1";
char ENGINE_Data[MAX_STR_SIZE] = "ENGINE v1";

DS_DATA DS_GENERATED_DATA[DATA_SIZE];

void Load_Data()
{
    DS_GENERATED_DATA[CLUTCH].data = &CLUTCH_Data;
    DS_GENERATED_DATA[GEAR_BOX].data = &GEAR_BOX_Data;
    DS_GENERATED_DATA[BRAKE_PEDAL].data = &BRAKE_PEDAL_Data;
    DS_GENERATED_DATA[ENGINE].data = &ENGINE_Data;
}