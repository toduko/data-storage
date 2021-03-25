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

      if (Is_Not_Int(element))
      {
        status = TYPE_ERROR;
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
      if (Is_Not_String(element))
      {
        status = TYPE_ERROR;
      }
      else
      {
        String *ptr = (String *)element.data;
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

    if (Is_Not_Int(element))
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
        if (Is_Not_In_S16_Bounds(value))
        {
          status = INT_VALUE_OVERFLOW;
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
        if (Is_Not_In_S8_Bounds(value))
        {
          status = INT_VALUE_OVERFLOW;
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
      if (Is_Not_String(element))
      {
        status = TYPE_ERROR;
      }
      else
      {
        String *ptr = (String *)element.data;
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

DSError DS_ReadIntList(const DSID id, const U8 position, S32 *value)
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
      if (Is_Not_IntList(element))
      {
        status = TYPE_ERROR;
      }
      else
      {
        S32 el_val;
        if (element.type == TYPE_S32_LIST)
        {
          S32_LIST *data = element.data;
          if (position >= data->size)
          {
            status = OUT_OF_BOUNDS;
          }
          else
          {
            *value = data->values[position];
          }
        }

        if (element.type == TYPE_S16_LIST)
        {
          S16_LIST *data = element.data;
          S16 val = data->values[position];
          if (position >= data->size)
          {
            status = OUT_OF_BOUNDS;
          }
          else
          {
            if (Is_Big_Endian())
            {
              el_val = ((S8 *)&val)[0] << 24 | (((S8 *)&val)[1] << 16);
            }
            else
            {
              el_val = ((S8 *)&val)[0] << 0 | (((S8 *)&val)[1] << 8);
            }
            *value = el_val;
          }
        }

        if (element.type == TYPE_S8_LIST)
        {
          S8_LIST *data = element.data;
          S8 val = data->values[position];
          if (position >= data->size)
          {
            status = OUT_OF_BOUNDS;
          }
          else
          {
            if (Is_Big_Endian())
            {
              el_val = ((S8 *)&val)[0] << 24;
            }
            else
            {
              el_val = ((S8 *)&val)[0] << 0;
            }
            *value = el_val;
          }
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  return status;
}

DSError DS_WriteIntList(const DSID id, const U8 position, const S32 value)
{
  DSError status = SUCCESS;

  if (id >= DC_ID_MAX)
  {
    status = OUT_OF_BOUNDS;
  }
  else
  {
    DS_DATA element = Get_Element_By_Id(id);
    if (Is_Not_IntList(element))
    {
      status = TYPE_ERROR;
    }
    else
    {
      if (element.type == TYPE_S32_LIST)
      {
        S32_LIST *data = element.data;
        if (position >= data->size)
        {
          status = OUT_OF_BOUNDS;
        }
        else
        {
          data->values[position] = value;
        }
      }

      if (element.type == TYPE_S16_LIST)
      {
        S16_LIST *data = element.data;
        if (position >= data->size)
        {
          status = OUT_OF_BOUNDS;
        }
        else
        {
          if (Is_Not_In_S16_Bounds(value))
          {
            status = INT_VALUE_OVERFLOW;
          }
          else
          {
            S16 s16arr[2];
            S32_To_S16_Lit_End(value, s16arr);
            data->values[position] = s16arr[0] | s16arr[1];
          }
        }
      }

      if (element.type == TYPE_S8_LIST)
      {
        S8_LIST *data = element.data;
        if (position >= data->size)
        {
          status = OUT_OF_BOUNDS;
        }
        else
        {
          if (Is_Not_In_S8_Bounds(value))
          {
            status = INT_VALUE_OVERFLOW;
          }
          else
          {
            S8 s8arr[4];
            S32_To_S8_Lit_End(value, s8arr);
            data->values[position] = s8arr[0] | s8arr[3];
          }
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  return status;
}

DSError DS_ReadStringList(const DSID id, const U8 position, char *buff, const U32 BuffSize)
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
      if (Is_Not_StringList(element))
      {
        status = TYPE_ERROR;
      }
      else
      {
        STRING_LIST *data = element.data;
        if (position >= data->size)
        {
          status = OUT_OF_BOUNDS;
        }
        else
        {
          char *ptr = &data->strings[position * data->max_str_size];
          if (BuffSize < data->max_str_size)
          {
            status = BUFFER_TOO_SMALL;
          }
          snprintf(buff, BuffSize, "%s", ptr);
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  return status;
}

DSError DS_WriteStringList(const DSID id, const U8 position, char *string)
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

      if (Is_Not_StringList(element))
      {
        status = TYPE_ERROR;
      }
      else
      {
        STRING_LIST *data = element.data;
        if (position >= data->size)
        {
          status = OUT_OF_BOUNDS;
        }
        else
        {
          char *ptr = &data->strings[position * data->max_str_size];
          if (strlen(string) > data->max_str_size)
          {
            status = BUFFER_TOO_BIG;
          }
          snprintf(ptr, data->max_str_size, "%s", string);
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  return status;
}