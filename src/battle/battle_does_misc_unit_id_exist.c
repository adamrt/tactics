#include "psx/types.h"

extern u8* battle_get_unit_misc_data_by_misc_id(u32 misc_id);

s32 battle_does_misc_unit_id_exist(u32 misc_id) {
    return battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff) != 0;
}
