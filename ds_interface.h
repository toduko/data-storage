#ifndef DS_INTERFACE_H_
#define DS_INTERFACE_H_

#include "generated_data.h"
#include <stdio.h>

extern bool DEBUG;

DSError DS_ReadInt(const DSID id, S32 *value);

DSError DS_ReadString(const DSID id, char *buff, const U32 BuffSize);

DSError DS_WriteInt(const DSID id, const S32 value);

DSError DS_WriteString(const DSID id, char *string);

#endif