#include "psx/types.h"

extern u8 D_800BF790[];

void battle_copy_other_spr_palette_data_to_ram(u8* src) {
    s32 i = 0;
    s32 one = 1;
    u8* dst = &D_800BF790[0];
    do {
        u8 v;
        s32 t;
        if (i & 1) {
            t = i;
            if (i < 0) {
                t = i + 0x1F;
            }
            if ((i - ((t >> 5) << 5)) != one) {
                v = *src++ | 0x80;
                goto store;
            }
        }
        v = *src++;
    store:
        *dst++ = v;
        i++;
    } while (i < 0x2A0);
}
