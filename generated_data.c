#include "generated_data.h"

/*
** INTEGERS
*/

S32 CLUTCH_Data;
S32 GEAR_BOX_Data;

/*
** STRINGS
*/

#define BRAKE_PEDAL_Size 9
char BRAKE_PEDAL_Str[BRAKE_PEDAL_Size] = "BRK";
String BRAKE_PEDAL_Data = {.size = BRAKE_PEDAL_Size, .str = BRAKE_PEDAL_Str};

#define ENGINE_Size 10
char ENGINE_Str[ENGINE_Size] = "ENG";
String ENGINE_Data = {.size = ENGINE_Size, .str = ENGINE_Str};

/*
** DATA INITIALIZATION
*/

DS_DATA DS_GENERATED_DATA[DC_ID_MAX] = {
    {.data = &BRAKE_PEDAL_Data, .type = STRING},
    {.data = &CLUTCH_Data, .type = INT},
    {.data = &GEAR_BOX_Data, .type = INT},
    {.data = &ENGINE_Data, .type = STRING},
};

DS_DATA Get_Element_By_Id(DSID id)
{
    return DS_GENERATED_DATA[id];
}