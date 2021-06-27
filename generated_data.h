#ifndef GENERATED_IDS_H_
#define GENERATED_IDS_H_

#include "types.h"
#include "generated_ids.h"

#define NUM_CONST_RELATIONS 3
extern const Relationship const_relationships[NUM_CONST_RELATIONS];

#define NUM_RELATIONS 7
extern Relationship dynamic_relationships[NUM_RELATIONS];;

DS_DATA Get_Element_By_Id(DSID id);

void Notify_Relations(DSID id);

#endif
