typedef signed int S32;     // -2147483648 to 2147483647
typedef unsigned int U32;   // 0 to 4294967295
typedef unsigned char DSID; // Data Storage ID 0 to 255

typedef enum // Status codes
{
  SUCCESS = 0,
  NOT_FOUND = 1,
} DSError;

typedef struct
{
  S32 s32Data;
  char *StringData;
} DS_Data;

typedef struct
{
  DSID id;
  char *code;
} DS_ID;
