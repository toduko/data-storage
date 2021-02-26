#include "types.h"
#include "helpers.h"
#include <stdio.h>
#include <string.h>

// data
#define DATA_SIZE 3
DS_Data DS_GENERATED_DATA[DATA_SIZE];
DS_ID DS_GENERATED_IDs[DATA_SIZE];

// seeding data
void Generate_Example_Data()
{
  for (int i = 0; i < DATA_SIZE; ++i)
  {
    DS_GENERATED_DATA[i].s32Data = i * 10;
    char str[i + 1];
    rand_string(str, 4);
    DS_GENERATED_DATA[i].StringData = str;
  }
}

void Generate_Example_Ids()
{
  for (int i = 0; i < DATA_SIZE; ++i)
  {
    DS_GENERATED_IDs[i].id = i;
    sprintf(DS_GENERATED_IDs[i].code, "%d", i);
  }
}

// interface
DSError DS_ReadInt(DSID id, S32 *value)
{
  for (int i = 0; i < DATA_SIZE; ++i)
  {
    if (id == DS_GENERATED_IDs[i].id)
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
    if (id == DS_GENERATED_IDs[i].id)
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
    if (id == DS_GENERATED_IDs[i].id)
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
    if (id == DS_GENERATED_IDs[i].id)
    {
      snprintf(DS_GENERATED_DATA[i].StringData, sizeof(string), "%s", string);
      return SUCCESS;
    }
  }
  return NOT_FOUND;
}