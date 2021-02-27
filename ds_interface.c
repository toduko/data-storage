#include "ds_interface.h"
#include "generated_ids.h"
#include "types.h"
#include <stdio.h>

DS_DATA DS_GENERATED_DATA[DATA_SIZE];

void Seed_Data()
{
  for (int i = 0; i < DATA_SIZE; ++i)
  {
    if (i % 2 == 1)
    {
      S32 intData;
      DS_GENERATED_DATA[i].data = &intData;
    }
  }
}

void Log_Result(const char *func, DSError status)
{
  char *code;
  switch (status)
  {
  case SUCCESS:
    code = "SUCCESS";
    break;
  case OUT_OF_BOUNDS:
    code = "OUT_OF_BOUNDS";
    break;
  case POINTER_ERROR:
    code = "POINTER_ERROR";
    break;
  }
  printf("%s result: %s\n", func, code);
}

DSError DS_ReadInt(DSID id, S32 *value)
{
  if (id >= DATA_SIZE)
  {
    Log_Result(__func__, OUT_OF_BOUNDS);
    return OUT_OF_BOUNDS;
  }
  S32 *ptr = (S32 *)DS_GENERATED_DATA[id].data;
  if (ptr)
  {
    *value = *ptr;
  }
  else
  {
    Log_Result(__func__, POINTER_ERROR);
    return POINTER_ERROR;
  }
  Log_Result(__func__, SUCCESS);
  return SUCCESS;
}

DSError DS_ReadString(DSID id, char *buff, U32 BuffSize)
{
  if (id >= DATA_SIZE)
  {
    Log_Result(__func__, OUT_OF_BOUNDS);
    return OUT_OF_BOUNDS;
  }
  snprintf(buff, BuffSize, "%s", (char *)DS_GENERATED_DATA[id].data);
  Log_Result(__func__, SUCCESS);
  return SUCCESS;
}

DSError DS_WriteInt(DSID id, S32 value)
{
  if (id >= DATA_SIZE)
  {
    Log_Result(__func__, OUT_OF_BOUNDS);
    return OUT_OF_BOUNDS;
  }
  S32 *ptr = (S32 *)DS_GENERATED_DATA[id].data;
  if (ptr)
  {
    *ptr = value;
  }
  else
  {
    Log_Result(__func__, POINTER_ERROR);
    return POINTER_ERROR;
  }
  Log_Result(__func__, SUCCESS);
  return SUCCESS;
}

DSError DS_WriteString(DSID id, char *string)
{
  if (id >= DATA_SIZE)
  {
    printf("DS_WriteString result: OUT_OF_BOUNDS\n");
    return OUT_OF_BOUNDS;
  }
  DS_GENERATED_DATA[id].data = string;
  printf("DS_WriteString result: SUCCESS\n");
  return SUCCESS;
}