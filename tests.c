#include "acutest.h"
#include "ds_interface.h"
#include "generated_data.h"
#include "tests.h"

void Print_Case_Number(DSID i)
{
    char case_str[MAX_STR_SIZE];
    sprintf(case_str, "%d", i);
    TEST_CASE(case_str);
}

void Test_LoadData(void)
{
    DSID i;
    for (i = 0; i < DC_ID_MAX; ++i)
    {
        Print_Case_Number(i);

        DS_DATA element = Get_Element_By_Id(i);
        void *ptr = element.data;
        TEST_CHECK(ptr != NULL);
        TEST_MSG("Expected: != %p", NULL);
        TEST_MSG("Produced: %p", ptr);
    }
}

void Test_ReadWriteInt(void)
{
    S32 s32Data;
    DSError status;

    DSID i;
    for (i = 0; i < DC_ID_MAX; ++i)
    {
        Print_Case_Number(i);

        DS_DATA element = Get_Element_By_Id(i);
        S32 val_to_write = i * 10;

        status = DS_WriteInt(i, val_to_write);
        if (element.type == INT)
        {
            TEST_CHECK(status == SUCCESS);
            TEST_MSG("Expected: %d", SUCCESS);
            TEST_MSG("Produced: %d", status);
        }
        else
        {
            TEST_CHECK(status == TYPE_ERROR);
            TEST_MSG("Expected: %d", TYPE_ERROR);
            TEST_MSG("Produced: %d", status);
        }
        status = DS_ReadInt(i, &s32Data);
        if (element.type == INT)
        {
            TEST_CHECK(status == SUCCESS);
            TEST_MSG("Expected: %d", SUCCESS);
            TEST_MSG("Produced: %d", status);

            TEST_CHECK(s32Data == val_to_write);
            TEST_MSG("Expected: %d", val_to_write);
            TEST_MSG("Produced: %d", s32Data);
        }
        else
        {
            TEST_CHECK(status == TYPE_ERROR);
            TEST_MSG("Expected: %d", TYPE_ERROR);
            TEST_MSG("Produced: %d", status);
        }
    }

    TEST_CASE("OUT_OF_BOUNDS");
    status = DS_WriteInt(DC_ID_MAX, s32Data);
    TEST_CHECK(status == OUT_OF_BOUNDS);
    TEST_MSG("Expected: %d", OUT_OF_BOUNDS);
    TEST_MSG("Produced: %d", status);

    status = DS_ReadInt(DC_ID_MAX, &s32Data);
    TEST_CHECK(status == OUT_OF_BOUNDS);
    TEST_MSG("Expected: %d", OUT_OF_BOUNDS);
    TEST_MSG("Produced: %d", status);
}

void Test_ReadWriteString(void)
{
    char str[MAX_STR_SIZE];
    DSID status;

    DSID i;
    for (i = 0; i < DC_ID_MAX; ++i)
    {
        Print_Case_Number(i);

        DS_DATA element = Get_Element_By_Id(i);
        char str_to_write[MAX_STR_SIZE];
        sprintf(str_to_write, "%d", i * 10);

        status = DS_WriteString(i, str_to_write);
        if (element.type == STRING)
        {
            TEST_CHECK(status == SUCCESS);
            TEST_MSG("Expected: %d", SUCCESS);
            TEST_MSG("Produced: %d", status);
        }
        else
        {
            TEST_CHECK(status == TYPE_ERROR);
            TEST_MSG("Expected: %d", TYPE_ERROR);
            TEST_MSG("Produced: %d", status);
        }
        status = DS_ReadString(i, str, sizeof(str));
        if (element.type == STRING)
        {
            TEST_CHECK(status == SUCCESS);
            TEST_MSG("Expected: %d", SUCCESS);
            TEST_MSG("Produced: %d", status);

            TEST_CHECK(strcmp(str, str_to_write) == 0);
            TEST_MSG("Expected: %s", str_to_write);
            TEST_MSG("Produced: %s", str);
        }
        else
        {
            TEST_CHECK(status == TYPE_ERROR);
            TEST_MSG("Expected: %d", TYPE_ERROR);
            TEST_MSG("Produced: %d", status);
        }
    }

    TEST_CASE("OUT_OF_BOUNDS");
    status = DS_WriteString(DC_ID_MAX, str);
    TEST_CHECK(status == OUT_OF_BOUNDS);
    TEST_MSG("Expected: %d", OUT_OF_BOUNDS);
    TEST_MSG("Produced: %d", status);

    status = DS_ReadString(DC_ID_MAX, str, sizeof(str));
    TEST_CHECK(status == OUT_OF_BOUNDS);
    TEST_MSG("Expected: %d", OUT_OF_BOUNDS);
    TEST_MSG("Produced: %d", status);
}

TEST_LIST = {
    {"Load Data", Test_LoadData},
    {"Read/Write Int", Test_ReadWriteInt},
    {"Read/Write String", Test_ReadWriteString},
    {NULL, NULL}};