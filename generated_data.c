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
** INTERER LISTS
*/

#define WHEEL_Size 3
S32 WHEEL_Values[WHEEL_Size] = {1, 2, 3};
INT_LIST WHEEL_Data = {.size = WHEEL_Size, .values = WHEEL_Values};

/*
** STRING LISTS
*/

#define SUSPENSION_Size 2
#define SUSPENSION_MAX_STR_Size 5

char SUSPENSION_Str1[SUSPENSION_MAX_STR_Size];
char SUSPENSION_Str2[SUSPENSION_MAX_STR_Size];

STRING_LIST SUSPENSION_Data = {.size = SUSPENSION_Size, .strings = {SUSPENSION_Str1, SUSPENSION_Str2}, .max_str_size = SUSPENSION_MAX_STR_Size};

/*
** DATA INITIALIZATION
*/

DS_DATA DS_GENERATED_DATA[DC_ID_MAX] = {
    {.type = TYPE_STRING, .data = &BRAKE_PEDAL_Data},
    {.type = TYPE_S8, .data = &CLUTCH_Data},
    {.type = TYPE_S16, .data = &GEAR_BOX_Data},
    {.type = TYPE_STRING, .data = &ENGINE_Data},
    {.type = TYPE_INT_LIST, .data = &WHEEL_Data},
    {.type = TYPE_STRING_LIST, .data = &SUSPENSION_Data},
};

DS_DATA Get_Element_By_Id(DSID id)
{
    return DS_GENERATED_DATA[id];
}
