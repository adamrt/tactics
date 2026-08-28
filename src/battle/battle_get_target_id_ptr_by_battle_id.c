#include "psx/types.h"

extern u8* get_unit_misc_data_by_unit_id(u32 unit_id);

u8* battle_get_target_id_ptr_by_battle_id(u32 battle_id) {
    u8* unit = get_unit_misc_data_by_unit_id(battle_id & 0xffff);

    if (unit == 0) {
        return 0;
    }
    return unit + 0x15c;
}
