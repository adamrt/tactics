#include "fft/battle.h"
#include "psx/types.h"

typedef struct ATEntry {
    u8 unit;
    u8 flags;
    u16 tick;
} ATEntry;

extern battle_stats_t battle_stats[];

s32 battle_at_list_sorting(s32 unit_id, s32 mode, u16 tick, ATEntry* list) {
    battle_stats_t* unit;
    s32 i;
    s32 j;
    s32 v;
    s32 t;
    s32 w;
    s32 cmp;

    unit = &battle_stats[unit_id];
    for (i = 0; i < 0x28; i++) {
        cmp = tick < list[i].tick;
        w = unit_id + 0x40;
        if (cmp) {
            for (j = 0x27; j > i; j--) {
                list[j] = list[j - 1];
            }
            v = unit_id;
            list[i].tick = tick;
            if (mode != 0) {
                v = w;
                if (unit->last_skillset_id == 0x12) {
                    v = unit_id + 0x60;
                } else {
                    t = unit->last_ability_id;
                    list[i].flags = t;
                    if (t >= 0x100) {
                        v = unit_id - 0x40;
                    }
                }
            }
            list[i].unit = v;
            break;
        }
    }
    return i != 0x28;
}
