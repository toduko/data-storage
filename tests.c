#include "tests.h"
#include "ds_interface.h"

void test(void)
{
    TEST_ASSERT(1);
}

TEST_LIST = {
    {"always true", test},
    {NULL, NULL}};