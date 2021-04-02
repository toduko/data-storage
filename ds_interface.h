#ifndef DS_INTERFACE_H_
#define DS_INTERFACE_H_

#include "types.h"
#include "generated_ids.h"

DSError DS_ReadInt(const DSID id, S32 *value);

DSError DS_ReadString(const DSID id, char *buff, const U32 BuffSize);

DSError DS_WriteInt(const DSID id, const S32 value);

DSError DS_WriteString(const DSID id, char *string);

DSError DS_ReadIntList(const DSID id, const U8 position, S32 *value);

DSError DS_ReadStringList(const DSID id, const U8 position, char *buff, const U32 BuffSize);

DSError DS_WriteIntList(const DSID id, const U8 position, const S32 value);

DSError DS_WriteStringList(const DSID id, const U8 position, char *string);

void DS_SetLanguage(Language NewLang);

#endif