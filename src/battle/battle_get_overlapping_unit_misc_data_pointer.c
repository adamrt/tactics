#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* g_misc_unit_list_head;
extern s32 g_casting_unit_misc_id;

battle_misc_data_t* battle_get_overlapping_unit_misc_data_pointer(battle_misc_data_t* self, s32 x, s32 y, s32 z) {
    battle_misc_data_t* list[16];
    battle_misc_data_t* unit;
    battle_stats_t* stats;
    s32 n;
    s32 i;

    n = 0;
    unit = g_misc_unit_list_head;
    if (unit != 0) {
        do {
            if (unit != self && unit->map_x == x && unit->map_y == y && unit->map_z == z) {
                stats = unit->battle_data;
                if (stats != 0 && stats->entd_slot != 0xFF) {
                    if (self->mount_rider_value == 0 || unit->unit_id != self->mount_rider_id) {
                        list[n] = unit;
                        n += 1;
                    }
                }
            }
            unit = (battle_misc_data_t*)unit->previous;
        } while (unit != 0);
    }
    if (n != 0) {
        for (i = 0; i < n; i++) {
            if (list[i]->unit_id == g_casting_unit_misc_id) {
                return list[i];
            }
        }
        return list[0];
    }
    return 0;
}
