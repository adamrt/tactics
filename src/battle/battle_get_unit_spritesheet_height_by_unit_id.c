#include "psx/types.h"

extern u8* get_unit_misc_data_by_unit_id(u32 unit_id);
extern u32 battle_get_unit_spritesheet_height(u8* unit);

u32 battle_get_unit_spritesheet_height_by_unit_id(u32 unit_id) {
    return battle_get_unit_spritesheet_height(get_unit_misc_data_by_unit_id(unit_id & 0xffff));
}
