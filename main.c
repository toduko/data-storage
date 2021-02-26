#include "ds_interface.h"

int main()
{
    char str[MAX_STR_SIZE];

    DS_ReadString(BRAKE_PEDAL, str, sizeof(str));
    printf("str value before: %s\n", str);

    DS_WriteString(BRAKE_PEDAL, "BRAKE");
    DS_ReadString(BRAKE_PEDAL, str, sizeof(str));
    printf("str value after: %s\n", str);

    S32 s32Data;

    DS_ReadInt(CLUTCH, &s32Data);
    printf("s32 value before: %d\n", s32Data);

    DS_WriteInt(CLUTCH, 321);
    DS_ReadInt(CLUTCH, &s32Data);
    printf("s32 value after: %d\n", s32Data);

    return 0;
}
