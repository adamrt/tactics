#include "psx/types.h"

extern u16 world_get_misc_id(u16 unit_id);

s32 world_try_get_unit_misc_data_by_id(u16* unit_id, s32* misc_index) {
    s32 index;
    s32 result;
    u16 id;

    id = *unit_id;
    if (id != 0) {
        if (id < 0x100) {
            *unit_id = world_get_misc_id(id);
            *misc_index = 0;
            if (*unit_id != 2000) {
                goto success;
            }
            result = 0;
            goto done;
        }
        index = id - 0xfe;
        if (id != 0) {
            goto store_index;
        }
    }
    index = 1;
store_index:
    *misc_index = index;
success:
    result = 1;
done:
    return result;
}
