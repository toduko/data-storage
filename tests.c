#include "tests.h"
#include "ds_interface.h"

void Test_ReadWriteInt(void)
{
    Load_Data();   

    S32 s32Data;
    DSError status;

    status = DS_WriteInt(CLUTCH, 321);
    TEST_CHECK(status == SUCCESS);
    TEST_MSG("Expected: %d", SUCCESS);
    TEST_MSG("Produced: %d", status);

    status = DS_ReadInt(CLUTCH, &s32Data);
    TEST_CHECK(status == SUCCESS);
    TEST_MSG("Expected: %d", SUCCESS);
    TEST_MSG("Produced: %d", status);

    TEST_CHECK(s32Data == 321);
    TEST_MSG("Expected: %d", 321);
    TEST_MSG("Produced: %d", s32Data);

    status = DS_ReadInt(ENGINE, &s32Data);
    TEST_CHECK(status == SUCCESS);
    TEST_MSG("Expected: %d", SUCCESS);
    TEST_MSG("Produced: %d", status);

    status = DS_ReadInt(DATA_SIZE, &s32Data);
    TEST_CHECK(status == OUT_OF_BOUNDS);
    TEST_MSG("Expected: %d", OUT_OF_BOUNDS);
    TEST_MSG("Produced: %d", status);
}

TEST_LIST = {
    {"Read/Write Int", Test_ReadWriteInt},
    {NULL, NULL}};