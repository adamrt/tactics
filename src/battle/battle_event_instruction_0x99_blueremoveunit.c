#include "psx/types.h"

typedef struct {
    u8 pad0[5];
    u8 x5;
    u8 pad6[0x15B];
    u8 x161;
} battle_stats_t;

extern s32 battle_does_misc_unit_id_exist(s32);
extern s32 battle_get_battle_unit_index_by_misc_id(s32);
extern battle_stats_t* battle_get_battle_stats_from_battle_id(s32);
extern battle_stats_t* find_unit_by_id(s32, s32*);
extern void battle_prepare_misc_unit_palette_modulation(s32, s32, s32, s32, s32);

void battle_event_instruction_0x99_blueremoveunit(s32 arg0) {
    s32 i;
    s32 idx;
    battle_stats_t* unit;
    s32 out[2];

    for (i = 0; i < 0x15; i++) {
        if (battle_does_misc_unit_id_exist(i) == 0) {
            continue;
        }
        idx = battle_get_battle_unit_index_by_misc_id(i);
        if (idx == -1) {
            continue;
        }
        unit = find_unit_by_id(battle_get_battle_stats_from_battle_id(idx)->x161, out);
        if ((unit->x5 & 0x30) == 0) {
            continue;
        }
        if (out[0] == -2) {
            continue;
        }
        if (unit->x161 != arg0) {
            continue;
        }
        battle_prepare_misc_unit_palette_modulation(i, 2, -0x1F, -0x1F, 0);
    }
}
