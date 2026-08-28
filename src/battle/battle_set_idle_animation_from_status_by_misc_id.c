#include "psx/types.h"

extern u8* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void set_idle_animation_from_status(u8* unit);

void battle_set_idle_animation_from_status_by_misc_id(u32 misc_id) {
    set_idle_animation_from_status(battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff));
}
