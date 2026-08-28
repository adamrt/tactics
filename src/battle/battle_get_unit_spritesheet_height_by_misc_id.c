#include "psx/types.h"

extern u8* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern u32 battle_get_unit_spritesheet_height(u8* unit);

u32 battle_get_unit_spritesheet_height_by_misc_id(u32 misc_id) {
    return battle_get_unit_spritesheet_height(battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff));
}
