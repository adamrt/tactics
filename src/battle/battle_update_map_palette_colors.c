#include "psx/types.h"

extern void update_map_palette_colors_inner(s32 mode, s32 palette_group,
    s32 palette_index,
    const u16* colors);
extern s32 g_map_palette_upload_pending;

void battle_update_map_palette_colors(s32 mode, s32 palette_group, s32 palette_index,
    s32 update_all, const u16* colors) {
    s32 index;

    if (update_all == 1) {
        const u16* current_colors;

        index = 0;
        current_colors = colors;
        while (index < 16) {
            update_map_palette_colors_inner(mode, palette_group, index,
                current_colors);
            index++;
            current_colors += 16;
        }
        g_map_palette_upload_pending = 1;
    } else {
        update_map_palette_colors_inner(mode, palette_group, palette_index,
            colors);
        g_map_palette_upload_pending = 1;
    }
}
