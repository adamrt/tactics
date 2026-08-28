#include "psx/types.h"

extern s32 battle_get_map_coords_from_misc_id(u32 misc_id, s16* coords);

void battle_copy_map_coords_from_misc_id(u32 misc_id, s16* coords) {
    battle_get_map_coords_from_misc_id(misc_id, coords);
}
