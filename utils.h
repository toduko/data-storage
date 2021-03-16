#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include "types.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

void Log_Result(const char *name, const DSError status);

void S32_To_S8_Lit_End(S32 src, S8 *dest);

S32 S8_To_S32_Lit_End(S8 *src);

void S32_To_S16_Lit_End(S32 src, S16 *dest);

S16 S16_To_S32_Lit_End(S16 *src);

U8 Is_Big_Endian();

#endif
