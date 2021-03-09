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
    DS_DATA element = Get_Element_By_Id(id);
    S32 *ptr = (S32 *)element.data;
    if (ptr)
    {
      if (element.type != INT)
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
    DS_DATA element = Get_Element_By_Id(id);
    char *ptr = (char *)element.data;
    if (ptr)
    {
      if (element.type != STRING)
      {
        status = TYPE_ERROR;
        snprintf(buff, BuffSize, "%s", "");
      }
      else
      {
        U32 data_len = strlen(ptr);
        if (BuffSize < data_len)
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
  DS_DATA element = Get_Element_By_Id(id);
  S32 *ptr = (S32 *)element.data;
  if (ptr)
  {
    if (element.type != INT)
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
  DS_DATA element = Get_Element_By_Id(id);
  char *ptr = (char *)element.data;
  if (ptr)
  {
    if (element.type != STRING)
    {
      status = TYPE_ERROR;
    }
    else
    {
      if (strlen(string) > strlen(ptr))
      {
        status = BUFFER_TOO_BIG;
      }
      else
      {
        snprintf(ptr, strlen(string) + 1, "%s", string);
      }
    }
  }
  else
  {
    status = POINTER_ERROR;
  }
  Log_Result(__FUNCTION__, status);
  return status;
}