#include "ds_interface.h"
#include "utils.h"

DSError DS_ReadInt(const DSID id, S32 *value)
{
  DSError status = SUCCESS;
  if (id >= DATA_SIZE)
  {
    Log_Result(__FUNCTION__, OUT_OF_BOUNDS);
    status = OUT_OF_BOUNDS;
  }
  else
  {
    S32 *ptr = (S32 *)DS_GENERATED_DATA[id].data;
    if (ptr)
    {
      *value = *ptr;
      Log_Result(__FUNCTION__, SUCCESS);
    }
    else
    {
      Log_Result(__FUNCTION__, POINTER_ERROR);
      status = POINTER_ERROR;
    }
  }
  return status;
}

DSError DS_ReadString(const DSID id, char *buff, const U32 BuffSize)
{
  DSError status = SUCCESS;
  if (id >= DATA_SIZE)
  {
    Log_Result(__FUNCTION__, OUT_OF_BOUNDS);
    status = OUT_OF_BOUNDS;
  }
  else
  {
    char *ptr = (char *)DS_GENERATED_DATA[id].data;
    if (ptr)
    {
      snprintf(buff, BuffSize, "%s", ptr);
      Log_Result(__FUNCTION__, SUCCESS);
    }
    else
    {
      snprintf(buff, BuffSize, "%s", "");
      Log_Result(__FUNCTION__, POINTER_ERROR);
      status = POINTER_ERROR;
    }
  }
  return status;
}

DSError DS_WriteInt(const DSID id, const S32 value)
{
  DSError status = SUCCESS;
  if (id >= DATA_SIZE)
  {
    Log_Result(__FUNCTION__, OUT_OF_BOUNDS);
    status = OUT_OF_BOUNDS;
  }
  S32 *ptr = (S32 *)DS_GENERATED_DATA[id].data;
  if (ptr)
  {
    *ptr = value;
    Log_Result(__FUNCTION__, SUCCESS);
  }
  else
  {
    Log_Result(__FUNCTION__, POINTER_ERROR);
    status = POINTER_ERROR;
  }

  return status;
}

DSError DS_WriteString(const DSID id, char *string)
{
  DSError status = SUCCESS;
  if (id >= DATA_SIZE)
  {
    printf("DS_WriteString result: OUT_OF_BOUNDS\n");
    status = OUT_OF_BOUNDS;
  }
  char *ptr = (char *)DS_GENERATED_DATA[id].data;
  if (ptr)
  {
    snprintf(ptr, sizeof(string), "%s", string);
    Log_Result(__FUNCTION__, SUCCESS);
  }
  else
  {
    Log_Result(__FUNCTION__, POINTER_ERROR);
    status = POINTER_ERROR;
  }

  return status;
}