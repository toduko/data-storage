#ifndef DS_INTERFACE_H_
#define DS_INTERFACE_H_

#include "generated_data.h"
#include <stdio.h>

DSError Set_Location(DSID id, void *location);

void Log_Result(const char *func, DSError status);

DSError DS_ReadInt(DSID id, S32 *value);

DSError DS_ReadString(DSID id, char *buff, U32 BuffSize);

DSError DS_WriteInt(DSID id, S32 value);

DSError DS_WriteString(DSID id, char *string);

#endif