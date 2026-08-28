#include "psx/types.h"

extern s32 g_battle_action_state;
extern s32 rand(void);

u8 battle_generate_treasure(u8* p) {
    u8 buf[8];
    s32 n;
    s32 i;
    u32 c;
    u8* q;

    if (g_battle_action_state != 0) {
        return;
    }

    q = p;
    n = 0;
    for (i = 0; i < 7; i++) {
        buf[n] = *(q + i + 0x1A);
        c = buf[n];
        if (c >= 0xFE) {
            continue;
        }
        if (c == 0) {
            continue;
        }
        n++;
    }

    if (n == 0) {
        buf[0] = ((rand() * 13) / 0x8000) - 0x10;
        if (buf[0] >= 0xF5) {
            buf[0] = buf[0] + 1;
        }
        n = 1;
    }

    i = (rand() * n) / 0x8000;
    return buf[i];
}
