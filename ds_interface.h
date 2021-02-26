#include "types.h"
#include <stdio.h>

// data
DS_Data DS_GENERATED_DATA[DATA_SIZE];
DSID DS_GENERATED_IDs[DATA_SIZE];

// seeding data
void Seed_Example_Ids()
{
  for (int i = 0; i < DATA_SIZE; ++i)
  {
    DS_GENERATED_IDs[i] = i; // id will be the same as index
  }
}

// interface
DSError DS_ReadInt(DSID id, S32 *value)
{
  for (int i = 0; i < DATA_SIZE; ++i)
  {
    if (id == DS_GENERATED_IDs[i])
    {
      *value = DS_GENERATED_DATA[i].s32Data;
      return SUCCESS;
    }
  }
  return NOT_FOUND;
}

DSError DS_ReadString(DSID id, char *buff, U32 BuffSize)
{
  for (int i = 0; i < DATA_SIZE; ++i)
  {
    if (id == DS_GENERATED_IDs[i])
    {
      snprintf(buff, BuffSize, "%s", DS_GENERATED_DATA[i].StringData);
      return SUCCESS;
    }
  }
  return NOT_FOUND;
}

DSError DS_WriteInt(DSID id, S32 value)
{
  for (int i = 0; i < DATA_SIZE; ++i)
  {
    if (id == DS_GENERATED_IDs[i])
    {
      DS_GENERATED_DATA[i].s32Data = value;
      return SUCCESS;
    }
  }
  return NOT_FOUND;
}

DSError DS_WriteString(DSID id, char *string)
{
  for (int i = 0; i < DATA_SIZE; ++i)
  {
    if (id == DS_GENERATED_IDs[i])
    {
      snprintf(DS_GENERATED_DATA[i].StringData, MAX_STR_SIZE, "%s", string);
      return SUCCESS;
    }
  }
  return NOT_FOUND;
}