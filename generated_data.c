#include "generated_data.h"
#include <stdio.h>

S32 CLUTCH_Data;
S32 GEAR_BOX_Data;
char BRAKE_PEDAL_Data[MAX_STR_SIZE] = "BRAKE v1";
char ENGINE_Data[MAX_STR_SIZE] = "ENGINE v1";

DS_DATA DS_GENERATED_DATA[DATA_SIZE] = {
    {.data = &BRAKE_PEDAL_Data, .type = STRING},
    {.data = &CLUTCH_Data, .type = INT},
    {.data = &GEAR_BOX_Data, .type = INT},
    {.data = &ENGINE_Data, .type = STRING},
};

DS_DATA Get_Element_By_Id(DSID id)
{
    return DS_GENERATED_DATA[id];
}