#include "generated_data.h"

/*
** INTEGERS
*/

S8 CLUTCH_Data;
S16 GEAR_BOX_Data;

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
    {.type = TYPE_STRING, .data = &BRAKE_PEDAL_Data},
    {.type = TYPE_S8, .data = &CLUTCH_Data},
    {.type = TYPE_S16, .data = &GEAR_BOX_Data},
    {.type = TYPE_STRING, .data = &ENGINE_Data},
};

DS_DATA Get_Element_By_Id(DSID id)
{
    return DS_GENERATED_DATA[id];
}
