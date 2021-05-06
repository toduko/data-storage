#ifndef QUEUE_H_
#define QUEUE_H_

#include "types.h"
#include "generated_ids.h"

typedef DSID QUEUE_DATA;

int Is_Empty();

int Is_Full();

DSError Enqueue(QUEUE_DATA data);

DSError Dequeue();

QUEUE_DATA Front();

void Print_Elements();

#endif
