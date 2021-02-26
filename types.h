typedef signed int S32;   // -2147483648 to 2147483647
typedef unsigned int U32; // 0 to 4294967295
typedef unsigned char UC; // 0 to 255

#define MAX_STR_SIZE 256

typedef enum // Status codes
{
  SUCCESS,
  NOT_FOUND,
} DSError;

typedef enum
{
  BRAKE_PEDAL,
  CLUTCH,
  GEAR_BOX,
  DATA_SIZE
} DSID;

typedef struct
{
  S32 s32Data;
  char StringData[MAX_STR_SIZE];
} DS_Data;