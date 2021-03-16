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

      if (element.type == TYPE_STRING)
      {
        status = TYPE_ERROR;
        *value = 0;
      }
      else
      {
        S32 el_val;
        if (element.type == TYPE_S32)
        {
          el_val = *((S32 *)element.data);
          *value = el_val;
        }
        if (element.type == TYPE_S16)
        {
          if (Is_Big_Endian())
          {
            el_val = ((S8 *)element.data)[0] << 24 | (((S8 *)element.data)[1] << 16);
          }
          else
          {
            el_val = ((S8 *)element.data)[0] << 0 | (((S8 *)element.data)[1] << 8);
          }
          *value = el_val;
        }
        if (element.type == TYPE_S8)
        {
          if (Is_Big_Endian())
          {
            el_val = ((S8 *)element.data)[0] << 24;
          }
          else
          {
            el_val = ((S8 *)element.data)[0] << 0;
          }
          *value = el_val;
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
      String *ptr = (String *)element.data;
      if (element.type != TYPE_STRING)
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
  if (id >= DC_ID_MAX)
  {
    status = OUT_OF_BOUNDS;
  }
  else
  {
    DS_DATA element = Get_Element_By_Id(id);

    if (element.type == TYPE_STRING)
    {
      status = TYPE_ERROR;
    }
    else
    {
      if (element.type == TYPE_S32)
      {
        S32 *ptr = (S32 *)element.data;
        *ptr = value;
      }
      if (element.type == TYPE_S16)
      {
        if (value > S16_MAX || value < S16_MIN)
        {
          status = INT_SIZE_ERROR;
        }
        else
        {
          S16 *ptr = (S16 *)element.data;
          S16 s16arr[2];
          S32_To_S16_Lit_End(value, s16arr);
          *ptr = s16arr[0] | s16arr[1];
        }
      }
      if (element.type == TYPE_S8)
      {
        if (value > S8_MAX || value < S8_MIN)
        {
          status = INT_SIZE_ERROR;
        }
        else
        {
          S8 *ptr = (S8 *)element.data;
          S8 s8arr[4];
          S32_To_S8_Lit_End(value, s8arr);
          *ptr = s8arr[0] | s8arr[3];
        }
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
      String *ptr = (String *)element.data;

      if (element.type != TYPE_STRING)
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
