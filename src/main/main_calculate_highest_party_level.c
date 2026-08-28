#include "psx/types.h"

extern u8* main_get_party_data_pointer(s32 slot);

extern u8 g_highest_party_level;

u8 main_calculate_highest_party_level(void) {
    u8 highest;
    s32 i;
    u8* unit;

    highest = 0;
    i = 0;
    do {
        unit = main_get_party_data_pointer(i);
        i += 1;
        if (unit[1] != 0xFF) {
            if (highest < unit[0x16]) {
                highest = unit[0x16];
            }
        }
    } while (i < 20);
    if (highest >= 0x64) {
        highest = 0x63;
    }
    g_highest_party_level = (u8)highest;
    return (u8)highest;
}
