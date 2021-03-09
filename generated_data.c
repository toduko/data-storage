#include "generated_data.h"
#include <stdio.h>

S32 CLUTCH_Data;
S32 GEAR_BOX_Data;
String BRAKE_PEDAL_Data = {.size = 9, .str = "BREAK v1"};
String ENGINE_Data = {.size = 10, .str = "ENGINE v1"};

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