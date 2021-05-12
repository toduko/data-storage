#include "ds_interface.h"
#include "generated_data.h"
#include "utils.h"
#include "queue.h"
#include <math.h>
#include <string.h>

Language language = ENGLISH;
DSID subscribers[DC_ID_MAX / 8 + (DC_ID_MAX % 8 != 0)];

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
        if (element.type == TYPE_S32 || element.type == TYPE_STATIC_S32_MONO)
        {
          *value = *((S32 *)element.data);
        }
        if (element.type == TYPE_S16 || element.type == TYPE_STATIC_S16_MONO)
        {
          *value = S16_To_S32(*(S16 *)element.data);
        }
        if (element.type == TYPE_S8 || element.type == TYPE_STATIC_S8_MONO)
        {
          *value = S8_To_S32(*(S8 *)element.data);
        }
        if (element.type == TYPE_STATIC_S32)
        {
          *value = ((S32 *)element.data)[language];
        }
        if (element.type == TYPE_STATIC_S16)
        {
          *value = S16_To_S32(((S16 *)element.data)[language]);
        }
        if (element.type == TYPE_STATIC_S8)
        {
          *value = S8_To_S32(((S8 *)element.data)[language]);
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  if (status == SUCCESS)
  {
    SetBit(subscribers[id / 8], id % 8);
  }
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
        if (Is_Not_StaticString(element))
        {
          String *ptr = (String *)element.data;
          if (BuffSize < ptr->size)
          {
            status = BUFFER_TOO_SMALL;
          }
          snprintf(buff, BuffSize, "%s", ptr->str);
        }
        else
        {
          if (element.type == TYPE_STATIC_STRING)
          {
            String *ptr = (String *)element.data;
            if (BuffSize < ptr[language].size)
            {
              status = BUFFER_TOO_SMALL;
            }
            snprintf(buff, BuffSize, "%s", ptr[language].str);
          }
          else
          {
            char *ptr = (char *)element.data;
            if (BuffSize < strlen(ptr))
            {
              status = BUFFER_TOO_SMALL;
            }
            snprintf(buff, BuffSize, "%s", ptr);
          }
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  if (status == SUCCESS)
  {
    SetBit(subscribers[id / 8], id % 8);
  }
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

    if (Is_Not_WritableInt(element))
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
          *ptr = S32_To_S16(value);
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
          *ptr = S32_To_S8(value);
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  if (status == SUCCESS && BitVal(subscribers[id / 8], id % 8) == 1)
  {
    Enqueue(id);
  }
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
      if (Is_Not_WritableString(element))
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
  if (status == SUCCESS && BitVal(subscribers[id / 8], id % 8) == 1)
  {
    Enqueue(id);
  }
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
            *value = S16_To_S32(val);
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
            *value = S8_To_S32(val);
          }
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  if (status == SUCCESS)
  {
    SetBit(subscribers[id / 8], id % 8);
  }
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
            data->values[position] = S32_To_S16(value);
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
            data->values[position] = S32_To_S8(value);
          }
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);
  if (status == SUCCESS && BitVal(subscribers[id / 8], id % 8) == 1)
  {
    Enqueue(id);
  }
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
  if (status == SUCCESS)
  {
    SetBit(subscribers[id / 8], id % 8);
  }
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
  if (status == SUCCESS && BitVal(subscribers[id / 8], id % 8) == 1)
  {
    Enqueue(id);
  }
  return status;
}

void DS_SetLanguage(Language NewLang)
{
  language = NewLang;
}
