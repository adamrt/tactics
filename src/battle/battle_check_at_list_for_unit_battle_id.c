#include "fft/battle.h"

extern s32 func_801835A8(battle_stats_t* unit);
extern void func_8018370C(u8* buf, s32 arg1);

s32 battle_check_at_list_for_unit_battle_id(battle_stats_t* unit) {
    u8 buf[160];
    s32 i;
    u8* p;
    u8 target;

    if (unit->entd_slot == 0xFF)
        return -1;
    if (func_801835A8(unit) != 0)
        return -3;
    target = unit->misc_unit_id;
    func_8018370C(buf, 1);
    i = 0;
    p = buf;
    do {
        if ((p[0] & 0x1F) == (target & 0xFF)) {
            return i;
        }
        i += 1;
        p += 4;
    } while (i < 0x28);
    return -2;
}
