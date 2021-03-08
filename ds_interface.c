#include "ds_interface.h"
#include "utils.h"
#include <math.h>
#include <string.h>

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
      if (DS_GENERATED_DATA[id].type != INT)
      {
        status = TYPE_ERROR;
        *value = 0;
      }
      else
      {
        *value = *ptr;
      }
    }
    else
    {
      status = POINTER_ERROR;
    }
  }
#ifdef DEBUG
  Log_Result(__FUNCTION__, status);
#endif
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
      if (DS_GENERATED_DATA[id].type != STRING)
      {
        status = TYPE_ERROR;
        snprintf(buff, BuffSize, "%s", "");
      }
      else
      {
        U32 data_len = strlen(ptr);
        if (BuffSize > data_len)
        {
          status = BUFFER_TOO_BIG;
        }
        else if (BuffSize < data_len)
        {
          status = BUFFER_TOO_SMALL;
        }
        snprintf(buff, BuffSize, "%s", ptr);
      }
    }
    else
    {
      snprintf(buff, BuffSize, "%s", "");
      status = POINTER_ERROR;
    }
  }
#ifdef DEBUG
  Log_Result(__FUNCTION__, status);
#endif
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
    if (DS_GENERATED_DATA[id].type != INT)
    {
      status = TYPE_ERROR;
    }
    else
    {
      *ptr = value;
    }
  }
  else
  {
    status = POINTER_ERROR;
  }
#ifdef DEBUG
  Log_Result(__FUNCTION__, status);
#endif
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
    if (DS_GENERATED_DATA[id].type != STRING)
    {
      status = TYPE_ERROR;
    }
    else
    {
      snprintf(ptr, strlen(string) + 1, "%s", string);
    }
  }
  else
  {
    status = POINTER_ERROR;
  }
#ifdef DEBUG
  Log_Result(__FUNCTION__, status);
#endif
  return status;
}