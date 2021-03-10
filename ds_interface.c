#include "ds_interface.h"
#include "generated_data.h"
#include "utils.h"
#include <math.h>
#include <string.h>

DSError DS_ReadInt(const DSID id, S32 *value)
{
  DSError status = SUCCESS;
  if (!value)
  {
    status = POINTER_ERROR;
  }
  else
  {

    if (id >= DATA_SIZE)
    {
      status = OUT_OF_BOUNDS;
    }
    else
    {
      DS_DATA element = Get_Element_By_Id(id);
      S32 *ptr = (S32 *)element.data;

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
  }
  Log_Result(__FUNCTION__, status);
  return status;
}

DSError DS_ReadString(const DSID id, char *buff, const U32 BuffSize)
{
  DSError status = SUCCESS;
  if (!buff)
  {
    status = POINTER_ERROR;
  }
  else
  {
    if (id >= DATA_SIZE)
    {
      status = OUT_OF_BOUNDS;
    }
    else
    {
      DS_DATA element = Get_Element_By_Id(id);
      String *ptr = (String *)element.data;
      if (element.type != STRING)
      {
        status = TYPE_ERROR;
        snprintf(buff, BuffSize, "%s", "");
      }
      else
      {
        if (BuffSize < ptr->size)
        {
          status = BUFFER_TOO_SMALL;
        }
        snprintf(buff, BuffSize, "%s", ptr->str);
      }
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
  else
  {
    DS_DATA element = Get_Element_By_Id(id);
    S32 *ptr = (S32 *)element.data;
    if (element.type != INT)
    {
      status = TYPE_ERROR;
    }
    else
    {
      *ptr = value;
    }
  }
  Log_Result(__FUNCTION__, status);
  return status;
}

DSError DS_WriteString(const DSID id, char *string)
{
  DSError status = SUCCESS;
  if (!string)
  {
    status = POINTER_ERROR;
  }
  else
  {
    if (id >= DATA_SIZE)
    {
      status = OUT_OF_BOUNDS;
    }
    else
    {
      DS_DATA element = Get_Element_By_Id(id);
      String *ptr = (String *)element.data;

      if (element.type != STRING)
      {
        status = TYPE_ERROR;
      }
      else
      {
        if (strlen(string) > ptr->size)
        {
          status = BUFFER_TOO_BIG;
        }
        snprintf(ptr->str, ptr->size, "%s", string);
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  return status;
}