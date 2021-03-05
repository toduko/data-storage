#include "tests.h"

void test(void)
{
    TEST_ASSERT(1);
}

TEST_LIST = {
    {"always true", test},
    {NULL, NULL}};