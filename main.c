#include "ds_interface.h"

int main()
{
    Generate_Example_Data();
    Generate_Example_Ids();

    char str[0xFF];

    DS_ReadString(0, str, sizeof(str));
    printf("str value before: %s\n", str);

    DS_WriteString(0, "test");
    DS_ReadString(0, str, sizeof(str));
    printf("str value after: %s\n", str);

    S32 s32Data;

    DS_ReadInt(1, &s32Data);
    printf("s32 value before: %d\n", s32Data);

    DS_WriteInt(1, 321);
    DS_ReadInt(1, &s32Data);
    printf("s32 value after: %d\n", s32Data);

    return 0;
}
