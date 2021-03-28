#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include "types.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

void Log_Result(const char *name, const DSError status);

S8 S32_To_S8(S32 value);

S32 S8_To_S32(S8 value);

S16 S32_To_S16(S32 value);

S32 S16_To_S32(S16 value);

#endif
