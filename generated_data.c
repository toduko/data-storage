#include "generated_data.h"
#include "queue.h"

/*
** INTEGERS
*/

S8 CLUTCH_Data;
S16 GEAR_BOX_Data;
const S16 TIRE_Data = 10;

/*
** STRINGS
*/

#define BRAKE_PEDAL_Size 9
char BRAKE_PEDAL_Str[BRAKE_PEDAL_Size] = "BRK";
String BRAKE_PEDAL_Data = {.size = BRAKE_PEDAL_Size, .str = BRAKE_PEDAL_Str};
const char STEERING_Data[] = "STEERING";

const String SPEED_Data[NUM_LANGUAGES] = {{.size = 8, .str = "км/ч"}, {.size = 5, .str = "km/h"}};

#define ENGINE_Size 10
char ENGINE_Str[ENGINE_Size] = "ENG";
String ENGINE_Data = {.size = ENGINE_Size, .str = ENGINE_Str};

/*
** INTERER LISTS
*/

#define WHEEL_Size 3
S8 WHEEL_Values[WHEEL_Size] = {1, 2, 3};
S8_LIST WHEEL_Data = {.size = WHEEL_Size, .values = WHEEL_Values};

/*
** STRING LISTS
*/

#define SUSPENSION_Size 2
#define SUSPENSION_MAX_STR_Size 5

char SUSPENSION_Strings[SUSPENSION_Size * SUSPENSION_MAX_STR_Size];

STRING_LIST SUSPENSION_Data = {.size = SUSPENSION_Size, .strings = SUSPENSION_Strings, .max_str_size = SUSPENSION_MAX_STR_Size};

/*
** DATA INITIALIZATION
*/

DS_DATA DS_GENERATED_DATA[DC_ID_MAX] = {
    {.type = TYPE_STRING, .data = &BRAKE_PEDAL_Data},
    {.type = TYPE_S8, .data = &CLUTCH_Data},
    {.type = TYPE_S16, .data = &GEAR_BOX_Data},
    {.type = TYPE_STRING, .data = &ENGINE_Data},
    {.type = TYPE_S8_LIST, .data = &WHEEL_Data},
    {.type = TYPE_STRING_LIST, .data = &SUSPENSION_Data},
    {.type = TYPE_STATIC_STRING, .const_data = &SPEED_Data},
    {.type = TYPE_STATIC_S16_MONO, .const_data = &TIRE_Data},
    {.type = TYPE_STATIC_STRING_MONO, .const_data = &STEERING_Data}};

#define NUM_CONST_RELATIONS 2
const Relationship const_relationships[NUM_CONST_RELATIONS] = {
    {.element = ENGINE, .linkedElement = WHEEL},
    {.element = SUSPENSION, .linkedElement = SPEED}};

Relationship dynamic_relationships[NUM_RELATIONS];

DS_DATA Get_Element_By_Id(DSID id)
{
    return DS_GENERATED_DATA[id];
}

void Notify_Relations(DSID id)
{
    int lo = 0,
        hi = NUM_CONST_RELATIONS;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;

        if (const_relationships[mid].element < id)
        {
            hi = mid;
        }

        if (const_relationships[mid].element > id)
        {
            lo = mid + 1;
        }

        if (const_relationships[mid].element == id)
        {
            Enqueue(const_relationships[mid].linkedElement);
            Notify_Relations(const_relationships[mid].linkedElement);

            /* Search right for elements with the same DSID */
            int i;
            for (i = mid; i < hi; ++i)
            {
                if (const_relationships[i].element == id)
                {
                    Enqueue(const_relationships[i].linkedElement);
                    Notify_Relations(const_relationships[i].linkedElement);
                }
                else
                {
                    break;
                }
            }

            /* Search left for elements with the same DSID */
            for (i = mid; i > lo; --i)
            {
                if (const_relationships[i].element == id)
                {
                    Enqueue(const_relationships[i].linkedElement);
                    Notify_Relations(const_relationships[i].linkedElement);
                }
                else
                {
                    break;
                }
            }
        }
    }

    lo = 0,
    hi = NUM_RELATIONS;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;

        if (dynamic_relationships[mid].element < id)
        {
            hi = mid;
        }

        if (dynamic_relationships[mid].element > id)
        {
            lo = mid + 1;
        }

        if (dynamic_relationships[mid].element == id && dynamic_relationships[mid].element != dynamic_relationships[mid].linkedElement)
        {
            Enqueue(dynamic_relationships[mid].linkedElement);
            Notify_Relations(dynamic_relationships[mid].linkedElement);

            /* Search right for elements with the same DSID */
            int i;
            for (i = mid; i < hi; ++i)
            {
                if (dynamic_relationships[i].element == id && dynamic_relationships[i].element != dynamic_relationships[i].linkedElement)
                {
                    Enqueue(dynamic_relationships[i].linkedElement);
                    Notify_Relations(dynamic_relationships[i].linkedElement);
                }
                else
                {
                    break;
                }
            }

            /* Search left for elements with the same DSID */
            for (i = mid; i > lo; --i)
            {
                if (dynamic_relationships[i].element == id && dynamic_relationships[i].element != dynamic_relationships[i].linkedElement)
                {
                    Enqueue(dynamic_relationships[i].linkedElement);
                    Notify_Relations(dynamic_relationships[i].linkedElement);
                }
                else
                {
                    break;
                }
            }
        }
    }
}