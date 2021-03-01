#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include "types.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

void Log_Result(const char *name, const DSError status);

#endif