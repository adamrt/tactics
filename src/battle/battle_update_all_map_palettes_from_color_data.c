#include "psx/types.h"

extern void update_map_palette_from_color_data(
    s32 map_slot, s32 mode, s32 palette_index, s32 update_all,
    const void* color_data);

void battle_update_all_map_palettes_from_color_data(s32 map_slot,
    const void* color_data) {
    update_map_palette_from_color_data(map_slot, 0, 0, 1, color_data);
}
