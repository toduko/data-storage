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

typedef struct
{
  void *data;
} DS_DATA;

extern DS_DATA DS_GENERATED_DATA[DATA_SIZE];

void Load_Data();

#endif