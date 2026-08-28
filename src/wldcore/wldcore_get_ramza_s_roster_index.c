#include "psx/types.h"

extern u8* wldcore_get_party_data_pointer(s32);

s32 wldcore_get_ramza_s_roster_index(void) {
    s32 i;
    for (i = 0; i < 16; i++) {
        u8* p = wldcore_get_party_data_pointer(i);
        if (p[1] != 0xFF && p[0] != 0 && p[0] < 4) {
            return i;
        }
    }
    return i;
}
