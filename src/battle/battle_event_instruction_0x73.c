#include "psx/types.h"

extern s16 battle_load_halfword(u8* p);
extern void battle_store_halfword(u8* p, s16 value);

void battle_event_instruction_0x73(u8* p, s32* src) {
    u8* dst;
    s32 i;
    s32 v;
    s32 val;

    dst = p + 0xF;
    if (p[0xE] == 0x38) {
        dst = p + 0x12;
    }
    for (i = 0; i < 7; i++) {
        v = *src;
        if (i < 3) {
            v = v / 1024;
        }
        if (battle_load_halfword(p) == 10000) {
            val = 10000;
        } else {
            val = v + battle_load_halfword(p);
        }
        battle_store_halfword(dst, val);
        p += 2;
        dst += 2;
        src++;
    }
}
