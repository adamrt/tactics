#include "psx/types.h"

extern void update_map_palette_from_color_data(
    s32 map_slot, s32 mode, s32 palette_index, s32 update_all,
    const void* color_data);

void battle_update_map_palette_colors_by_index(s32 map_slot, s32 palette_index,
    const void* color_data) {
    s32 index;

    if (palette_index >= 16) {
        index = 0;
        do {
            update_map_palette_from_color_data(map_slot, 3, index, 0,
                color_data);
            index++;
        } while (index < 16);
    } else {
        update_map_palette_from_color_data(map_slot, 3, palette_index, 0,
            color_data);
    }
}
