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

    if (id >= DC_ID_MAX)
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
        if (element.size == S32_SIZE)
        {
          *value = *ptr;
        }
        if (element.size == S16_SIZE)
        {
          *value = (S16)*ptr;
        }
        if (element.size == S8_SIZE)
        {
          *value = (S8)*ptr;
        }
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
    if (id >= DC_ID_MAX)
    {
      status = OUT_OF_BOUNDS;
    }
    else
    {
      DS_DATA element = Get_Element_By_Id(id);
      char *ptr = (char *)element.data;
      if (element.type != STRING)
      {
        status = TYPE_ERROR;
        snprintf(buff, BuffSize, "%s", "");
      }
      else
      {
        if (BuffSize < element.size)
        {
          status = BUFFER_TOO_SMALL;
        }
        snprintf(buff, BuffSize, "%s", ptr);
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  return status;
}

DSError DS_WriteInt(const DSID id, const S32 value)
{
  DSError status = SUCCESS;
  if (id >= DC_ID_MAX)
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
        if (element.size == S32_SIZE)
        {
          *ptr = value;
        }
        if (element.size == S16_SIZE)
        {
          *ptr = (S16)value;
        }
        if (element.size == S8_SIZE)
        {
          *ptr= (S8)value;
        }
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
    if (id >= DC_ID_MAX)
    {
      status = OUT_OF_BOUNDS;
    }
    else
    {
      DS_DATA element = Get_Element_By_Id(id);
      char *ptr = (char *)element.data;

      if (element.type != STRING)
      {
        status = TYPE_ERROR;
      }
      else
      {
        if (strlen(string) > element.size)
        {
          status = BUFFER_TOO_BIG;
        }
        snprintf(ptr, element.size, "%s", string);
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  return status;
}
