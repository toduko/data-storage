#include "generated_data.h"
#include "utils.h"
#include "queue.h"

S32 BRAKE_PEDAL_1_Data;
S32 BRAKE_PEDAL_2_Data;

S16 BRAKE_PEDAL_3_Data;
S16 CLUTCH_1_Data;

S8 CLUTCH_2_Data;
S8 CLUTCH_3_Data;

#define GEAR_BOX_1_Size 10
char GEAR_BOX_1_Str[GEAR_BOX_1_Size] = "GB1";
String GEAR_BOX_1_Data = {.size = GEAR_BOX_1, .str = GEAR_BOX_1_Str};

#define GEAR_BOX_2_Size 10
char GEAR_BOX_2_Str[GEAR_BOX_1_Size] = "GB2";
String GEAR_BOX_2_Data = {.size = GEAR_BOX_2, .str = GEAR_BOX_2_Str};

#define GEAR_BOX_3_Size 3
S32 GEAR_BOX_3_Values[GEAR_BOX_3_Size] = {1, 2, 3};
S32_LIST GEAR_BOX_3_Data = {.size = GEAR_BOX_3_Size, .values = GEAR_BOX_3_Values};

#define ENGINE_1_Size 4
S32 ENGINE_1_Values[ENGINE_1_Size] = {1, 2, 3, 4};
S32_LIST ENGINE_1_Data = {.size = ENGINE_1_Size, .values = ENGINE_1_Values};

#define ENGINE_2_Size 3
S16 ENGINE_2_Values[ENGINE_2_Size] = {1, 2, 3};
S16_LIST ENGINE_2_Data = {.size = ENGINE_2_Size, .values = ENGINE_2_Values};

#define ENGINE_3_Size 4
S16 ENGINE_3_Values[ENGINE_3_Size] = {1, 2, 3, 4};
S16_LIST ENGINE_3_Data = {.size = ENGINE_3_Size, .values = ENGINE_3_Values};

#define WHEEL_1_Size 4
S8 WHEEL_1_Values[WHEEL_1_Size] = {1, 2, 3, 4};
S8_LIST WHEEL_1_Data = {.size = WHEEL_1_Size, .values = WHEEL_1_Values};

#define WHEEL_2_Size 3
S8 WHEEL_2_Values[WHEEL_2_Size] = {1, 2, 3};
S8_LIST WHEEL_2_Data = {.size = WHEEL_2_Size, .values = WHEEL_2_Values};

#define WHEEL_3_Size 2
#define WHEEL_3_MAX_STR_Size 5

char WHEEL_3_Strings[WHEEL_3_Size * WHEEL_3_MAX_STR_Size];

STRING_LIST WHEEL_3_Data = {.size = WHEEL_3_Size, .strings = WHEEL_3_Strings, .max_str_size = WHEEL_3_MAX_STR_Size};

#define SUSPENSION_1_Size 2
#define SUSPENSION_1_MAX_STR_Size 5

char SUSPENSION_1_Strings[SUSPENSION_1_Size * SUSPENSION_1_MAX_STR_Size];

STRING_LIST SUSPENSION_1_Data = {.size = SUSPENSION_1_Size, .strings = SUSPENSION_1_Strings, .max_str_size = SUSPENSION_1_MAX_STR_Size};

const String SUSPENSION_2_Data[NUM_LANGUAGES] = {{.size = 9, .str = "дата"}, {.size = 5, .str = "data"}};
const String SUSPENSION_3_Data[NUM_LANGUAGES] = {{.size = 9, .str = "дата"}, {.size = 5, .str = "data"}};

const S32 SPEED_1_Data[NUM_LANGUAGES] = {1, 2};
const S32 SPEED_2_Data[NUM_LANGUAGES] = {1, 2};

const S16 SPEED_3_Data[NUM_LANGUAGES] = {1, 2};
const S16 TIRE_1_Data[NUM_LANGUAGES] = {1, 2};

const S8 TIRE_2_Data[NUM_LANGUAGES] = {1, 2};
const S8 TIRE_3_Data[NUM_LANGUAGES] = {1, 2};

const S32 STEERING_1_Data = 1;
const S32 STEERING_2_Data = 1;

const S16 STEERING_3_Data = 1;
const S16 RADIO_1_Data = 1;

const S8 RADIO_2_Data = 1;
const S8 RADIO_3_Data = 1;

const char AIR_BAG_1_Data[] = "AB1";
const char AIR_BAG_2_Data[] = "AB2";

/*
** DATA INITIALIZATION
*/

DS_DATA DS_GENERATED_DATA[DC_ID_MAX] = {
    {.data = &BRAKE_PEDAL_1_Data},
    {.data = &BRAKE_PEDAL_2_Data},
    {.data = &BRAKE_PEDAL_3_Data},
    {.data = &CLUTCH_1_Data},
    {.data = &CLUTCH_2_Data},
    {.data = &CLUTCH_3_Data},
    {.data = &GEAR_BOX_1_Data},
    {.data = &GEAR_BOX_2_Data},
    {.data = &GEAR_BOX_3_Data},
    {.data = &ENGINE_1_Data},
    {.data = &ENGINE_2_Data},
    {.data = &ENGINE_3_Data},
    {.data = &WHEEL_1_Data},
    {.data = &WHEEL_2_Data},
    {.data = &WHEEL_3_Data},
    {.data = &SUSPENSION_1_Data},
    {.const_data = &SUSPENSION_2_Data},
    {.const_data = &SUSPENSION_3_Data},
    {.const_data = &SPEED_1_Data},
    {.const_data = &SPEED_2_Data},
    {.const_data = &SPEED_3_Data},
    {.const_data = &TIRE_1_Data},
    {.const_data = &TIRE_2_Data},
    {.const_data = &TIRE_3_Data},
    {.const_data = &STEERING_1_Data},
    {.const_data = &STEERING_2_Data},
    {.const_data = &STEERING_3_Data},
    {.const_data = &RADIO_1_Data},
    {.const_data = &RADIO_2_Data},
    {.const_data = &RADIO_3_Data},
    {.const_data = &AIR_BAG_1_Data},
    {.const_data = &AIR_BAG_2_Data}};

const Relationship const_relationships[NUM_CONST_RELATIONS] = {{.element = AIR_BAG_1, .linkedElement = AIR_BAG_2}};

Relationship dynamic_relationships[NUM_RELATIONS];

DS_DATA Get_Element_By_Id(DSID id)
{
    return DS_GENERATED_DATA[id];
}

void Notify_Relations(DSID id)
{
    int idx = binary_search_element(const_relationships, NUM_CONST_RELATIONS, id);

    if (idx != -1)
    {
        if (const_relationships[idx].element != const_relationships[idx].linkedElement)
        {
            Enqueue(const_relationships[idx].linkedElement);
            Notify_Relations(const_relationships[idx].linkedElement);
        }

        int left = idx, right = idx;

        while (left - 1 >= 0)
        {
            if (const_relationships[--left].element == id)
            {
                if (const_relationships[left].element != const_relationships[left].linkedElement)
                {
                    Enqueue(const_relationships[left].linkedElement);
                    Notify_Relations(const_relationships[left].linkedElement);
                }
            }
            else
            {
                break;
            }
        }

        while (right + 1 < NUM_CONST_RELATIONS)
        {
            if (const_relationships[++right].element == id)
            {
                if (const_relationships[right].element != const_relationships[right].linkedElement)
                {
                    Enqueue(const_relationships[right].linkedElement);
                    Notify_Relations(const_relationships[right].linkedElement);
                }
            }
            else
            {
                break;
            }
        }
    }

    idx = binary_search_element(dynamic_relationships, NUM_RELATIONS, id);
    if (idx != -1)
    {
        if (dynamic_relationships[idx].element != dynamic_relationships[idx].linkedElement)
        {
            Enqueue(dynamic_relationships[idx].linkedElement);
            Notify_Relations(dynamic_relationships[idx].linkedElement);
        }

        int left = idx, right = idx;

        while (left - 1 >= 0)
        {
            if (dynamic_relationships[--left].element == id)
            {
                if (dynamic_relationships[left].element != dynamic_relationships[left].linkedElement)
                {
                    Enqueue(dynamic_relationships[left].linkedElement);
                    Notify_Relations(dynamic_relationships[left].linkedElement);
                }
            }
            else
            {
                break;
            }
        }

        while (right + 1 < NUM_RELATIONS)
        {
            if (dynamic_relationships[++right].element == id)
            {
                if (dynamic_relationships[right].element != dynamic_relationships[right].linkedElement)
                {
                    Enqueue(dynamic_relationships[right].linkedElement);
                    Notify_Relations(dynamic_relationships[right].linkedElement);
                }
            }
            else
            {
                break;
            }
        }
    }
}