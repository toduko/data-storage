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

      if (element.type != INT)
      {
        status = TYPE_ERROR;
        *value = 0;
      }
      else
      {
        if (element.size == S32_SIZE)
        {
          S32 *ptr = (S32 *)element.data;
          *value = *ptr;
        }
        if (element.size == S16_SIZE)
        {
          S16 *ptr = (S16 *)element.data;
          U8 i;
          U8 ptr_idx;
          if (IS_BIG_ENDIAN)
          {
             /* Set last 16 bits of value to ptr */
            for (i = 31, ptr_idx = 15; i >= 16, ptr_idx >= 0; --i, --ptr_idx)
            {
              if (BitVal(*ptr, ptr_idx))
              {
                SetBit(*value, i);
              }
              else
              {
                ClearBit(*value, i);
              }
            }
            /* Clear remaining 16 bits */
            for (i = 15; i >= 0; --i)
            {
              ClearBit(*value, i);
            }
          }
          else
          {
             /* Set first 16 bits of value to ptr */
            for (i = 0; i < 16; ++i)
            {
              if (BitVal(*ptr, i))
              {
                SetBit(*value, i);
              }
              else
              {
                ClearBit(*value, i);
              }
            }
            /* Clear remaining 16 bits */
            for (i = 16; i < 32; ++i)
            {
              ClearBit(*value, i);
            }
          }
        }
        if (element.size == S8_SIZE)
        {
          S16 *ptr = (S16 *)element.data;
          U8 i;
          U8 ptr_idx;
          if (IS_BIG_ENDIAN)
          {
            /* Set last 8 bits of value to ptr */
            for (i = 31, ptr_idx = 7; i >= 24, ptr_idx >= 0; --i, --ptr_idx)
            {
              if (BitVal(*ptr, ptr_idx))
              {
                SetBit(*value, i);
              }
              else
              {
                ClearBit(*value, i);
              }
            }
            /* Clear remaining 24 bits */
            for (i = 23; i >= 0; --i)
            {
              ClearBit(*value, i);
            }
          }
          else
          {
            /* Set fisrt 8 bits of value to ptr */
            for (i = 0; i < 8; ++i)
            {
              if (BitVal(*ptr, i))
              {
                SetBit(*value, i);
              }
              else
              {
                ClearBit(*value, i);
              }
            }
            /* Clear remaining 24 bits */
            for (i = 8; i < 32; ++i)
            {
              ClearBit(*value, i);
            }
          }
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

    if (element.type != INT)
    {
      status = TYPE_ERROR;
    }
    else
    {
      if (element.size == S32_SIZE)
      {
        S32 *ptr = (S32 *)element.data;
        *ptr = value;
      }
      if (element.size == S16_SIZE)
      {
        if (value > S16_MAX || value < S16_MIN)
        {
          status = INT_SIZE_ERROR;
        }
        else
        {
          S16 *ptr = (S16 *)element.data;
          U8 i;
          U8 val_idx;
          if (IS_BIG_ENDIAN)
          {
            /* Set last 16 bits of ptr to value */
            for (i = 31, val_idx = 15; i >= 16, val_idx >= 0; --i, --val_idx)
            {
              if (BitVal(value, val_idx))
              {
                SetBit(*ptr, i);
              }
              else
              {
                ClearBit(*ptr, i);
              }
            }
          }
          else
          {
            /* Set first 16 bits of ptr to value */
            for (i = 0; i < 16; ++i)
            {
              if (BitVal(value, i))
              {
                SetBit(*ptr, i);
              }
              else
              {
                ClearBit(*ptr, i);
              }
            }
          }
        }
      }
      if (element.size == S8_SIZE)
      {
        if (value > S8_MAX || value < S8_MIN)
        {
          status = INT_SIZE_ERROR;
        }
        else
        {
          S8 *ptr = (S8 *)element.data;
          U8 i;
          U8 val_idx;
          if (IS_BIG_ENDIAN)
          {
            /* Set last 8 bits of ptr to value */
            for (i = 31, val_idx = 7; i >= 24, val_idx >= 0; --i, --val_idx)
            {
              if (BitVal(value, val_idx))
              {
                SetBit(*ptr, i);
              }
              else
              {
                ClearBit(*ptr, i);
              }
            }
          }
          else
          {
            /* Set first 8 bits of ptr to value */
            for (i = 0; i < 8; ++i)
            {
              if (BitVal(value, i))
              {
                SetBit(*ptr, i);
              }
              else
              {
                ClearBit(*ptr, i);
              }
            }
          }
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
