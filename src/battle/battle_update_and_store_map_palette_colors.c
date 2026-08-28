#include "psx/types.h"

extern void battle_update_map_palette_colors(s32 mode, s32 palette_group,
    s32 palette_index, s32 update_all,
    const u16* colors);
extern u16 g_map_palette_stored_colors[][0x4C1];

void battle_update_and_store_map_palette_colors(s32 mode, s32 palette_group,
    s32 palette_index, s32 update_all,
    const u16* colors) {
    s32 index;
    const u16* colors_reg = colors;

    battle_update_map_palette_colors(mode, palette_group, palette_index, update_all,
        colors_reg);

    if (update_all == 1) {
        u16* destination;
        const u16* source;

        index = 0;
        destination = g_map_palette_stored_colors[palette_group];
        source = colors_reg;
        while (index < 256) {
            *destination++ = *source++;
            index++;
        }
    } else {
        const u16* source;
        u16* palette_colors;
        s32 palette_offset;

        index = 0;
        palette_offset = palette_index * 16;
        palette_colors = g_map_palette_stored_colors[palette_group];
        source = colors_reg;
        while (index < 16) {
            palette_colors[palette_offset + index] = *source++;
            index++;
        }
    }
}
