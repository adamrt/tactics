#include "psx/types.h"

extern u8* battle_get_existent_battle_unit_pointer(s32 unit_id);
extern s32 func_801817C0(s32 a0, u8 a1, u16* a2, void* a3, void* sp10, s32 sp14, void* sp18, void* sp1c);

s32 battle_draw_out_2(s32 unit_id, u8 ability, u8* out) {
    u16 abilities[0x10];
    u8 sp40[0x10];
    u8 sp50[0x10];
    u8 sp60[0x10];
    u8 sp70[0x10];
    s32 n;
    s32 i;
    s32 count;
    u32 v;
    u32 w;

    count = 0;
    if (battle_get_existent_battle_unit_pointer(unit_id) == 0) {
        return 0;
    }
    if (ability != 0x13) {
        *out = 0xFF;
        return 0;
    }
    n = func_801817C0(unit_id, 0x13, abilities, sp40, sp60, 0, sp50, sp70);
    if (n == 0) {
        *out = 0xFF;
        return 0;
    }
    for (i = 0; i < n; i++) {
        v = abilities[i];
        if (v < 0x170) {
            w = v - 0x26;
            *out = w;
            out++;
            count++;
        }
    }
    *out = 0xFF;
    return count + 0x100;
}
