#include "ds_interface.h"

DS_DATA DS_GENERATED_DATA[DATA_SIZE];

DSError DS_ReadInt(DSID id, S32 *value) {
  if (id >= DATA_SIZE)
    return OUT_OF_BOUNDS;
  DS_GENERATED_DATA[id].data = value;
  return SUCCESS;
}

DSError DS_ReadString(DSID id, char *buff, U32 BuffSize) {
  if (id >= DATA_SIZE)
    return OUT_OF_BOUNDS;
  snprintf(buff, BuffSize, "%s", (char *)DS_GENERATED_DATA[id].data);
  return SUCCESS;
}

DSError DS_WriteInt(DSID id, S32 value) {
  if (id >= DATA_SIZE)
    return OUT_OF_BOUNDS;
  *((S32 *)DS_GENERATED_DATA[id].data) = value;
  return SUCCESS;
}

DSError DS_WriteString(DSID id, char *string) {
  if (id >= DATA_SIZE)
    return OUT_OF_BOUNDS;
  DS_GENERATED_DATA[id].data = string;
  return SUCCESS;
}