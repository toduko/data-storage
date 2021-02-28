#include "ds_interface.h"
#include <string.h>
#include <stdio.h>

DSError Set_Location(DSID id, void *location)
{
  if (id >= DATA_SIZE)
  {
    Log_Result(__func__, OUT_OF_BOUNDS);
    return OUT_OF_BOUNDS;
  }
  DS_GENERATED_DATA[id].data = location;
  Log_Result(__func__, SUCCESS);
  return SUCCESS;
}

void Log_Result(const char *func, DSError status)
{
  char output[MAX_STR_SIZE * 2];
  char *red = "\x1b[31m";
  char *green = "\x1b[32m";
  char *yellow = "\x1b[33m";
  switch (status)
  {
  case SUCCESS:
    strcpy(output, green);
    strcat(output, "SUCCESS");
    break;
  case OUT_OF_BOUNDS:
    strcpy(output, yellow);
    strcat(output, "OUT_OF_BOUNDS");
    break;
  case POINTER_ERROR:
    strcpy(output, red);
    strcat(output, "POINTER_ERROR");
    break;
  }
  printf("%s result: %s\n", func, output);
  printf("\x1b[0m");
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
  Log_Result(__func__, SUCCESS);
  return SUCCESS;
}