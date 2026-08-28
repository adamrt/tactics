#include "psx/types.h"

extern void update_unit_graphics_by_misc_id(u32 misc_id);

void battle_update_unit_graphics_by_misc_id_wrapper(u32 misc_id) {
    update_unit_graphics_by_misc_id(misc_id);
}
