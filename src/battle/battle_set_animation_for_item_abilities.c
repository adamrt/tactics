#include "fft/battle.h"
#include "psx/types.h"

extern void battle_store_item_display_data(battle_misc_data_t*, s32);
extern void battle_store_unit_animation_facing(s32, s32, battle_misc_data_t*);
extern void battle_store_unit_animation_facing_movement_data(s32, s32, battle_misc_data_t*);

void battle_set_animation_for_item_abilities(battle_misc_data_t* unit, battle_misc_data_t* target) {
    s32 dx;
    s32 dy;

    battle_store_item_display_data(unit, unit->used_item_or_weapon_id);
    if (target != 0) {
        dx = target->map_x - unit->map_x;
        dy = target->map_y - unit->map_y;
    } else {
        dx = 0;
        dy = 0;
    }
    if (dx < 0) {
        dx = -dx;
    }
    if (dy < 0) {
        dy = -dy;
    }
    /* facing is read signed (lh). */
    if ((dx <= 0 && dy <= 0) || (dx < 2 && dy == 0) || (dx == 0 && dy < 2)) {
        battle_store_unit_animation_facing(0x39, *(s16*)&unit->facing, unit);
    } else {
        /* 0x2d0: item display sub-record, not yet in the header. */
        unit->_unknown_299[0x2d0 - 0x299] = 0;
        battle_store_unit_animation_facing_movement_data(0x4C, *(s16*)&unit->facing, unit);
    }
}
