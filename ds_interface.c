#include "ds_interface.h"
#include "utils.h"
#include <math.h>

DSError DS_ReadInt(const DSID id, S32 *value)
{
  DSError status = SUCCESS;
  if (id >= DATA_SIZE)
  {
    status = OUT_OF_BOUNDS;
  }
  else
  {
    S32 *ptr = (S32 *)DS_GENERATED_DATA[id].data;
    if (ptr)
    {
      *value = *ptr;
    }
    else
    {
      status = POINTER_ERROR;
    }
  }
  Log_Result(__FUNCTION__, status);
  return status;
}

DSError DS_ReadString(const DSID id, char *buff, const U32 BuffSize)
{
  DSError status = SUCCESS;
  if (id >= DATA_SIZE)
  {
    status = OUT_OF_BOUNDS;
  }
  else
  {
    char *ptr = (char *)DS_GENERATED_DATA[id].data;
    if (ptr)
    {
      snprintf(buff, BuffSize, "%s", ptr);
      if (BuffSize < pow(2, sizeof(buff)))
      {

        status = BUFFER_TOO_SMALL;
      }
    }
    else
    {
      snprintf(buff, BuffSize, "%s", "");
      status = POINTER_ERROR;
    }
  }
  Log_Result(__FUNCTION__, status);
  return status;
}

DSError DS_WriteInt(const DSID id, const S32 value)
{
  DSError status = SUCCESS;
  if (id >= DATA_SIZE)
  {
    status = OUT_OF_BOUNDS;
  }
  S32 *ptr = (S32 *)DS_GENERATED_DATA[id].data;
  if (ptr)
  {
    *ptr = value;
  }
  else
  {
    status = POINTER_ERROR;
  }
  Log_Result(__FUNCTION__, status);
  return status;
}

DSError DS_WriteString(const DSID id, char *string)
{
  DSError status = SUCCESS;
  if (id >= DATA_SIZE)
  {
    status = OUT_OF_BOUNDS;
  }
  char *ptr = (char *)DS_GENERATED_DATA[id].data;
  if (ptr)
  {
    snprintf(ptr, sizeof(string), "%s", string);
  }
  else
  {
    status = POINTER_ERROR;
  }
  Log_Result(__FUNCTION__, status);
  return status;
}