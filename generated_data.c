#include "generated_data.h"

/*
** INTEGERS
*/

S8 CLUTCH_Data;
#define CLUTCH_Size S8_SIZE
S16 GEAR_BOX_Data;
#define GEAR_BOX_Size S16_SIZE

/*
** STRINGS
*/

#define BRAKE_PEDAL_Size 9
char BRAKE_PEDAL_Data[BRAKE_PEDAL_Size] = "BRK";
#define ENGINE_Size 10
char ENGINE_Data[ENGINE_Size] = "ENG";

/*
** DATA INITIALIZATION
*/

DS_DATA DS_GENERATED_DATA[DC_ID_MAX] = {
    {.type = STRING, .size = BRAKE_PEDAL_Size, .data = &BRAKE_PEDAL_Data},
    {.type = INT, .size = CLUTCH_Size, .data = &CLUTCH_Data},
    {.type = INT, .size = GEAR_BOX_Size,.data = &GEAR_BOX_Data},
    {.type = STRING, .size = ENGINE_Size, .data = &ENGINE_Data},
};

DS_DATA Get_Element_By_Id(DSID id)
{
    return DS_GENERATED_DATA[id];
}
