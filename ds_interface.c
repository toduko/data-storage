#include "ds_interface.h"
#include "utils.h"

DSError DS_ReadInt(const DSID id, S32 *value)
{
  if (id >= DATA_SIZE)
  {
    Log_Result(__FUNCTION__, OUT_OF_BOUNDS);
    return OUT_OF_BOUNDS;
  }
  S32 *ptr = (S32 *)DS_GENERATED_DATA[id].data;
  if (ptr)
  {
    *value = *ptr;
  }
  else
  {
    Log_Result(__FUNCTION__, POINTER_ERROR);
    return POINTER_ERROR;
  }
  Log_Result(__FUNCTION__, SUCCESS);
  return SUCCESS;
}

DSError DS_ReadString(const DSID id, char *buff, const U32 BuffSize)
{
  if (id >= DATA_SIZE)
  {
    Log_Result(__FUNCTION__, OUT_OF_BOUNDS);
    return OUT_OF_BOUNDS;
  }
  char *ptr = (char *)DS_GENERATED_DATA[id].data;
  if (ptr)
  {
    snprintf(buff, BuffSize, "%s", ptr);
  }
  else
  {
    snprintf(buff, BuffSize, "%s", "");
    Log_Result(__FUNCTION__, POINTER_ERROR);
    return POINTER_ERROR;
  }
  Log_Result(__FUNCTION__, SUCCESS);
  return SUCCESS;
}

DSError DS_WriteInt(const DSID id, const S32 value)
{
  if (id >= DATA_SIZE)
  {
    Log_Result(__FUNCTION__, OUT_OF_BOUNDS);
    return OUT_OF_BOUNDS;
  }
  S32 *ptr = (S32 *)DS_GENERATED_DATA[id].data;
  if (ptr)
  {
    *ptr = value;
  }
  else
  {
    Log_Result(__FUNCTION__, POINTER_ERROR);
    return POINTER_ERROR;
  }
  Log_Result(__FUNCTION__, SUCCESS);
  return SUCCESS;
}

DSError DS_WriteString(const DSID id, char *string)
{
  if (id >= DATA_SIZE)
  {
    printf("DS_WriteString result: OUT_OF_BOUNDS\n");
    return OUT_OF_BOUNDS;
  }
  char *ptr = (char *)DS_GENERATED_DATA[id].data;
  if (ptr)
    snprintf(ptr, sizeof(*ptr), "%s", string);
  else
  {
    Log_Result(__FUNCTION__, POINTER_ERROR);
    return POINTER_ERROR;
  }
  DS_GENERATED_DATA[id].data = string;
  Log_Result(__FUNCTION__, SUCCESS);
  return SUCCESS;
}