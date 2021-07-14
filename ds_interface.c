#include "ds_interface.h"
#include "generated_data.h"
#include "utils.h"
#include "queue.h"
#include <math.h>
#include <string.h>

static Language language = ENGLISH;
static U8 subscribers[(DC_ID_MAX + 7) / 8] = {0};

void Notify_Relations(DSID id)
{
  int idx = binary_search_element(const_relationships, NUM_CONST_RELATIONS, id);

  if (idx != -1)
  {
    if (const_relationships[idx].element != const_relationships[idx].linkedElement)
    {
      Enqueue(const_relationships[idx].linkedElement);
      Notify_Relations(const_relationships[idx].linkedElement);
    }

    int left = idx, right = idx;

    while (left - 1 >= 0)
    {
      if (const_relationships[--left].element == id)
      {
        if (const_relationships[left].element != const_relationships[left].linkedElement)
        {
          Enqueue(const_relationships[left].linkedElement);
          Notify_Relations(const_relationships[left].linkedElement);
        }
      }
      else
      {
        break;
      }
    }

    while (right + 1 < NUM_CONST_RELATIONS)
    {
      if (const_relationships[++right].element == id)
      {
        if (const_relationships[right].element != const_relationships[right].linkedElement)
        {
          Enqueue(const_relationships[right].linkedElement);
          Notify_Relations(const_relationships[right].linkedElement);
        }
      }
      else
      {
        break;
      }
    }
  }

  idx = binary_search_element(dynamic_relationships, NUM_RELATIONS, id);
  if (idx != -1)
  {
    if (dynamic_relationships[idx].element != dynamic_relationships[idx].linkedElement)
    {
      Enqueue(dynamic_relationships[idx].linkedElement);
      Notify_Relations(dynamic_relationships[idx].linkedElement);
    }

    int left = idx, right = idx;

    while (left - 1 >= 0)
    {
      if (dynamic_relationships[--left].element == id)
      {
        if (dynamic_relationships[left].element != dynamic_relationships[left].linkedElement)
        {
          Enqueue(dynamic_relationships[left].linkedElement);
          Notify_Relations(dynamic_relationships[left].linkedElement);
        }
      }
      else
      {
        break;
      }
    }

    while (right + 1 < NUM_RELATIONS)
    {
      if (dynamic_relationships[++right].element == id)
      {
        if (dynamic_relationships[right].element != dynamic_relationships[right].linkedElement)
        {
          Enqueue(dynamic_relationships[right].linkedElement);
          Notify_Relations(dynamic_relationships[right].linkedElement);
        }
      }
      else
      {
        break;
      }
    }
  }
}

DSError DS_ReadInt(const DSID id, S32 *value)
{
  DSError status = SUCCESS;

  if (value == NULL)
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
      if (!IS_INT(id))
      {
        status = TYPE_ERROR;
      }
      else
      {
        if (IS_S32(id) || IS_STATIC_S32_MONO(id))
        {
          *value = *((S32 *)element.data);
        }
        else if (IS_S16(id) || IS_STATIC_S16_MONO(id))
        {
          *value = S16_To_S32(*(S16 *)element.data);
        }
        else if (IS_S8(id) || IS_STATIC_S8_MONO(id))
        {
          *value = S8_To_S32(*(S8 *)element.data);
        }
        else if (IS_STATIC_S32(id))
        {
          *value = ((S32 *)element.data)[language];
        }
        else if (IS_STATIC_S16(id))
        {
          *value = S16_To_S32(((S16 *)element.data)[language]);
        }
        else if (IS_STATIC_S8(id))
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

/* MKO: never use char (you have predefined types) */
DSError DS_ReadString(const DSID id, char *buff, const U32 BuffSize)
{
  DSError status = SUCCESS;
  if (buff == NULL)
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
      if (!IS_GENERAL_STRING(id))
      {
        status = TYPE_ERROR;
      }
      else
      {

        if (IS_STRING(id))
        {
          const String *ptr = (String *)element.data;
          if (BuffSize < ptr->size)
          {
            status = BUFFER_TOO_SMALL;
          }
          else
          {
            memcpy(buff, ptr->str, BuffSize);
          }
        }
        else
        {
          if (IS_STATIC_STRING(id))
          {
            const String *ptr = (String *)element.data;
            if (BuffSize < ptr[language].size)
            {
              status = BUFFER_TOO_SMALL;
            }
            else
            {
              memcpy(buff, ptr[language].str, BuffSize);
            }
          }
          else if (IS_STATIC_STRING_MONO(id))
          {
            const char *ptr = (char *)element.data;
            if (BuffSize < strlen(ptr))
            {
              status = BUFFER_TOO_SMALL;
            }
            else
            {
              memcpy(buff, ptr, BuffSize);
            }
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

    if (!IS_WRITABLE_INT(id))
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
      else if (IS_S16(id))
      {
        if (Is_Not_In_S16_Bounds(value))
        {
          status = INT_VALUE_OVERFLOW;
        }
        else
        {
          S16 *ptr = (S16 *)element.data;
          S16 val_to_write = value & 0xFFFF;
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
      else if (IS_S8(id))
      {
        if (Is_Not_In_S8_Bounds(value))
        {
          status = INT_VALUE_OVERFLOW;
        }
        else
        {
          S8 *ptr = (S8 *)element.data;
          S8 val_to_write = value & 0xFF;
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

  if (string == NULL)
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
      if (!IS_STRING(id))
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
        else
        {
          if (memcmp(string, ptr->str, ptr->size) != 0)
          {
            memcpy(ptr->str, string, ptr->size);
          }
          else
          {
            status = SAME_VALUE;
          }
        }
      }
    }
  }
  /* MKO: we'll not want to use this log in production (release), therefore this code should exist only in debug */
  Log_Result(__FUNCTION__, status);
  if ((status == SUCCESS) && (BitVal(subscribers[id / 8], id % 8) == 1))
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
  if (value == NULL)
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
      if (!IS_INT_LIST(id))
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
        else if (IS_S16_LIST(id))
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
        else if (IS_S8_LIST(id))
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
    if (!IS_INT_LIST(id))
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
      else if (IS_S16_LIST(id))
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
            S16 val_to_write = value & 0xFFFF;
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
      else if (IS_S8_LIST(id))
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
            S8 val_to_write = value & 0xFF;
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
  if (buff == NULL)
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
      if (!IS_STRING_LIST(id))
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
          const char *ptr = &data->strings[position * data->max_str_size];
          if (BuffSize < data->max_str_size)
          {
            status = BUFFER_TOO_SMALL;
          }
          memcpy(buff, ptr, BuffSize);
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

  if (string == NULL)
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

      if (!IS_STRING_LIST(id))
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
            memcpy(ptr, string, data->max_str_size);
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
  /* TODO - add global counter of relationships */
  for (i = 0; i < NUM_RELATIONS; ++i)
  {
    if (dynamic_relationships[i].element == dynamic_relationships[i].linkedElement)
    {
      dynamic_relationships[i].element = updatedOne;
      dynamic_relationships[i].linkedElement = notifiedOne;
      break;
    }
  }

  for (i = 0; i < NUM_RELATIONS - 1; ++i)
  {
    if (dynamic_relationships[i].element > dynamic_relationships[i + 1].element)
    {
      Relationship temp = dynamic_relationships[i];
      dynamic_relationships[i] = dynamic_relationships[i + 1];
      dynamic_relationships[i + 1] = temp;
    }
  }
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

  for (i = 0; i < NUM_RELATIONS - 1; ++i)
  {
    if (dynamic_relationships[i].element > dynamic_relationships[i + 1].element)
    {
      Relationship temp = dynamic_relationships[i];
      dynamic_relationships[i] = dynamic_relationships[i + 1];
      dynamic_relationships[i + 1] = temp;
    }
  }
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