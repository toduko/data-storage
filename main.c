#include "ds_interface.h"
#include "helpers.h"

#define STR_SIZE 32

int main()
{
    Generate_Example_Ids();

    char str[STR_SIZE];
    char rnd_str[STR_SIZE];
    generate_random_string(rnd_str, STR_SIZE);

    DS_ReadString(0, str, sizeof(str));
    printf("str value before: %s\n", str);

    DS_WriteString(0, rnd_str);
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
