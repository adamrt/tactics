#include "psx/types.h"

extern s32 battle_get_map_coords_from_misc_id(s32 misc_id, s16* out);

s32 world_get_map_coords_from_misc_id(s32 misc_id, s16* out) {
    return battle_get_map_coords_from_misc_id(misc_id, out);
}
