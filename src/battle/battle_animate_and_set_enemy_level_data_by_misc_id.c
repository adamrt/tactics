#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void battle_set_enemy_level_data_by_battle_id(u32 battle_id);

s32 battle_animate_and_set_enemy_level_data_by_misc_id(u32 misc_id) {
    battle_misc_data_t* unit;
    battle_stats_t* battle_data;

    unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);
    if (unit != 0) {
        battle_data = unit->battle_data;
        /* 0x0a is a byte field in the header; the target stores a halfword. */
        *(u16*)&unit->ability_in_use = 1;
        /* 0x1d8: unit sprite graphic trigger (wiki), not yet in the header. */
        unit->sprite_graphic_trigger = 1;
        if (battle_data != 0) {
            battle_set_enemy_level_data_by_battle_id(battle_data->misc_unit_id);
        }
        return 1;
    }
    return 0;
}
