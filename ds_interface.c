#include "ds_interface.h"

DS_DATA DS_GENERATED_DATA[DATA_SIZE];

DSError DS_ReadInt(DSID id, S32 *value)
{
  if (id >= DATA_SIZE)
    return OUT_OF_BOUNDS;
  *value = DS_GENERATED_DATA[id].s32Data;
  return SUCCESS;
}

DSError DS_ReadString(DSID id, char *buff, U32 BuffSize)
{
  if (id >= DATA_SIZE)
    return OUT_OF_BOUNDS;
  snprintf(buff, BuffSize, "%s", DS_GENERATED_DATA[id].StringData);
  return SUCCESS;
}

DSError DS_WriteInt(DSID id, S32 value)
{
  if (id >= DATA_SIZE)
    return OUT_OF_BOUNDS;
  DS_GENERATED_DATA[id].s32Data = value;
  return SUCCESS;
}

DSError DS_WriteString(DSID id, char *string)
{
  if (id >= DATA_SIZE)
    return OUT_OF_BOUNDS;
  snprintf(DS_GENERATED_DATA[id].StringData, MAX_STR_SIZE, "%s", string);
  return SUCCESS;
}