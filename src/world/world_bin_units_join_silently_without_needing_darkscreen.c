#include "psx/types.h"

extern u8* battle_get_battle_stats_from_battle_id(s32);
extern u8* find_unit_by_id(u8 id, s32* out_index);
extern void save_unit_to_party(u8* unit, u32 flag);

void world_bin_units_join_silently_without_needing_darkscreen(void) {
    s32 out_idx;
    s32 i;
    u8* unit;
    u8 first;
    u8 flags;

    i = 0;
    do {
        unit = find_unit_by_id(battle_get_battle_stats_from_battle_id(i)[0x161], &out_idx);
        if (out_idx >= 0 && i == out_idx) {
            if (unit[2] == 0xFF || ((first = unit[0]) != 0 && first < 4)) {
                flags = unit[6];
                if (flags & 0x10) {
                    save_unit_to_party(unit, flags & 1);
                }
            }
        }
        i++;
    } while (i < 0x15);
}
