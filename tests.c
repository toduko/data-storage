#include "ds_interface.h"
#include "tests.h"

void Test_LoadData(void)
{
    Load_Data();
    DSID i;
    for (i = 0; i < DATA_SIZE; ++i)
    {
        void *ptr = DS_GENERATED_DATA[i].data;
        TEST_CHECK(ptr != NULL);
        TEST_MSG("Expected: != %p", NULL);
        TEST_MSG("Produced: %p", ptr);
    }
}

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

    status = DS_ReadInt(DATA_SIZE, &s32Data);
    TEST_CHECK(status == OUT_OF_BOUNDS);
    TEST_MSG("Expected: %d", OUT_OF_BOUNDS);
    TEST_MSG("Produced: %d", status);
}

void Test_ReadWriteString(void)
{
    Load_Data();

    char str[MAX_STR_SIZE];
    char str_to_write[] = "BRAKE v2";
    DSID status;

    status = DS_ReadString(BRAKE_PEDAL, str, sizeof(str));
    TEST_CHECK(status != POINTER_ERROR);
    TEST_MSG("Expected: != %d", POINTER_ERROR);
    TEST_MSG("Produced: %d", status);

    status = DS_WriteString(BRAKE_PEDAL, str_to_write);
    TEST_MSG("Expected: %d", SUCCESS);
    TEST_MSG("Produced: %d", status);

    status = DS_ReadString(BRAKE_PEDAL, str, sizeof(str));
    TEST_CHECK(status != POINTER_ERROR);
    TEST_MSG("Expected: != %d", POINTER_ERROR);
    TEST_MSG("Produced: %d", status);

    int string_comparison = strcmp(str, str_to_write) == 0;
    TEST_CHECK(string_comparison);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", string_comparison);
}

TEST_LIST = {
    {"Load Data", Test_LoadData},
    {"Read/Write Int", Test_ReadWriteInt},
    {"Read/Write String", Test_ReadWriteString},
    {NULL, NULL}};