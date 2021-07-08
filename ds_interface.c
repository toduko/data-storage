#include "ds_interface.h"
#include "generated_data.h"
#include "utils.h"
#include "queue.h"
#include <math.h>
#include <string.h>

Language language = ENGLISH;
static U8 subscribers[(DC_ID_MAX + 7) / 8] = {0};

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

      if (Is_Not_Int(id))
      {
        status = TYPE_ERROR;
      }
      else
      {
        if (IS_S32(id) || IS_STATIC_S32_MONO(id))
        {
          *value = *((S32 *)element.data);
        }
        if (IS_S16(id) || IS_STATIC_S16_MONO(id))
        {
          *value = S16_To_S32(*(S16 *)element.data);
        }
        if (IS_S8(id) || IS_STATIC_S8_MONO(id))
        {
          *value = S8_To_S32(*(S8 *)element.data);
        }
        if (IS_STATIC_S32(id))
        {
          *value = ((S32 *)element.data)[language];
        }
        if (IS_STATIC_S16(id))
        {
          *value = S16_To_S32(((S16 *)element.data)[language]);
        }
        if (IS_STATIC_S8(id))
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
      if (Is_Not_String(id))
      {
        status = TYPE_ERROR;
      }
      else
      {
        if (Is_Not_StaticString(id))
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
          if (IS_STATIC_STRING(id))
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
  DS_DATA element;

  if (id >= DC_ID_MAX)
  {
    status = OUT_OF_BOUNDS;
  }
  else
  {
    element = Get_Element_By_Id(id);

    if (Is_Not_WritableInt(id))
    {
      status = TYPE_ERROR;
    }
    else
    {
      if (IS_S32(id))
      {
        S32 *ptr = (S32 *)element.data;
        if (value != *ptr)
        {
          *ptr = value;
        }
        else
        {
          status = SAME_VALUE;
        }
      }
      if (IS_S16(id))
      {
        if (Is_Not_In_S16_Bounds(value))
        {
          status = INT_VALUE_OVERFLOW;
        }
        else
        {
          S16 *ptr = (S16 *)element.data;
          S16 val_to_write = S32_To_S16(value);
          if (val_to_write != *ptr)
          {
            *ptr = val_to_write;
          }
          else
          {
            status = SAME_VALUE;
          }
        }
      }
      if (IS_S8(id))
      {
        if (Is_Not_In_S8_Bounds(value))
        {
          status = INT_VALUE_OVERFLOW;
        }
        else
        {
          S8 *ptr = (S8 *)element.data;
          S8 val_to_write = S32_To_S8(value);
          if (val_to_write != *ptr)
          {
            *ptr = val_to_write;
          }
          else
          {
            status = SAME_VALUE;
          }
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);

  if (status == SUCCESS && BitVal(subscribers[id / 8], id % 8) == 1)
  {
    Enqueue(id);
    ClearBit(subscribers[id / 8], id % 8);
    Notify_Relations(id);
  }

  return status;
}

DSError DS_WriteString(const DSID id, char *string)
{
  DSError status = SUCCESS;
  DS_DATA element;

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
      element = Get_Element_By_Id(id);
      if (Is_Not_WritableString(id))
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
        if (memcmp(string, ptr->str, ptr->size) != 0)
        {
          snprintf(ptr->str, ptr->size, "%s", string);
        }
        else
        {
          status = SAME_VALUE;
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);

  if (status == SUCCESS && BitVal(subscribers[id / 8], id % 8) == 1)
  {
    Enqueue(id);
    ClearBit(subscribers[id / 8], id % 8);
    Notify_Relations(id);
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
      if (Is_Not_IntList(id))
      {
        status = TYPE_ERROR;
      }
      else
      {
        if (IS_S32_LIST(id))
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

        if (IS_S16_LIST(id))
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

        if (IS_S8_LIST(id))
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
  DS_DATA element;

  if (id >= DC_ID_MAX)
  {
    status = OUT_OF_BOUNDS;
  }
  else
  {
    element = Get_Element_By_Id(id);
    if (Is_Not_IntList(id))
    {
      status = TYPE_ERROR;
    }
    else
    {
      if (IS_S32_LIST(id))
      {
        S32_LIST *data = element.data;
        if (position >= data->size)
        {
          status = OUT_OF_BOUNDS;
        }
        else
        {
          if (value != data->values[position])
          {
            data->values[position] = value;
          }
          else
          {
            status = SAME_VALUE;
          }
        }
      }

      if (IS_S16_LIST(id))
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
            S16 val_to_write = S32_To_S16(value);
            if (val_to_write != data->values[position])
            {
              data->values[position] = val_to_write;
            }
            else
            {
              status = SAME_VALUE;
            }
          }
        }
      }

      if (IS_S8_LIST(id))
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
            S8 val_to_write = S32_To_S8(value);
            if (val_to_write != data->values[position])
            {
              data->values[position] = val_to_write;
            }
            else
            {
              status = SAME_VALUE;
            }
          }
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);

  if (status == SUCCESS && BitVal(subscribers[id / 8], id % 8) == 1)
  {
    Enqueue(id);
    ClearBit(subscribers[id / 8], id % 8);
    Notify_Relations(id);
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
      if (Is_Not_StringList(id))
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
  DS_DATA element;

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
      element = Get_Element_By_Id(id);

      if (Is_Not_StringList(id))
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
          if (memcmp(string, ptr, data->max_str_size) != 0)
          {
            snprintf(ptr, data->max_str_size, "%s", string);
          }
          else
          {
            status = SAME_VALUE;
          }
        }
      }
    }
  }
  Log_Result(__FUNCTION__, status);

  if (status == SUCCESS && BitVal(subscribers[id / 8], id % 8) == 1)
  {
    Enqueue(id);
    ClearBit(subscribers[id / 8], id % 8);
    Notify_Relations(id);
  }

  return status;
}

void DS_SetLanguage(Language NewLang)
{
  language = NewLang;
}

void DS_AddNotification(DSID updatedOne, DSID notifiedOne)
{
  int i;

  for (i = 0; i < NUM_RELATIONS; ++i)
  {
    if (dynamic_relationships[i].element == dynamic_relationships[i].linkedElement)
    {
      dynamic_relationships[i].element = updatedOne;
      dynamic_relationships[i].linkedElement = notifiedOne;
      break;
    }
  }
  sort_relations(dynamic_relationships, 0, NUM_RELATIONS - 1);
}

void DS_RemoveNotification(DSID updatedOne)
{
  int i;
  for (i = 0; i < NUM_RELATIONS; ++i)
  {
    if (dynamic_relationships[i].element == updatedOne)
    {
      dynamic_relationships[i].linkedElement = dynamic_relationships[i].element;
    }
  }

  sort_relations(dynamic_relationships, 0, NUM_RELATIONS - 1);
}

void DS_ExchangeNotification(DSID src, DSID dst)
{
  int i;
  for (i = 0; i < NUM_RELATIONS; ++i)
  {
    if (dynamic_relationships[i].linkedElement == dst)
    {
      dynamic_relationships[i].linkedElement = dynamic_relationships[i].element;
    }

    if (dynamic_relationships[i].linkedElement == src && dynamic_relationships[i].element != dynamic_relationships[i].linkedElement)
    {
      DS_AddNotification(dynamic_relationships[i].element, dst);
    }
  }

  for (i = 0; i < NUM_CONST_RELATIONS; ++i)
  {
    if (const_relationships[i].linkedElement == src && const_relationships[i].element != const_relationships[i].linkedElement)
    {
      DS_AddNotification(const_relationships[i].element, dst);
    }
  }
}

void DS_LinksUpdate(DSID id, const DSID *pDSList, const S32 listSize)
{
  int i;
  for (i = 0; i < listSize; ++i)
  {
    DS_AddNotification(id, pDSList[i]);
  }
}