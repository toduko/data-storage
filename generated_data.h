#ifndef GENERATED_IDS_H_
#define GENERATED_IDS_H_
#include "types.h"

typedef enum
{
    BRAKE_PEDAL,
    CLUTCH,
    GEAR_BOX,
    ENGINE,
    DATA_SIZE
} DSID;

void Load_Data();
DS_DATA Get_Element_By_Id(DSID id);

#endif