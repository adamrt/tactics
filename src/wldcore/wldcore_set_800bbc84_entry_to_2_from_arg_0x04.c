#include "psx/types.h"

typedef struct {
    s32 value;
    s8 rest[48];
} WldcoreEntry52;

extern WldcoreEntry52 D_800BBC84[];

void wldcore_set_800bbc84_entry_to_2_from_arg_0x04(s32* param) {
    D_800BBC84[param[1]].value = 2;
}
