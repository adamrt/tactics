#include "psx/types.h"

extern u16 g_map_palette_stored_colors[][0x4C1];
extern u16 g_map_palette_modified_colors[][0x100];

void battle_store_modified_map_palette_colors(s32 palette_group, s32 palette_index,
    s32 store_all) {
    if (store_all == 1) {
        u16* destination;
        u16* source;

        store_all = 0;
        destination = g_map_palette_stored_colors[palette_group];
        source = g_map_palette_modified_colors[0];
        source += palette_group * 0x100;
        while (store_all < 256) {
            *destination++ = *source++;
            store_all++;
        }
    } else {
        u16* stored_palette_group;
        s32 stored_palette_group_offset;

        store_all = 0;
        palette_index *= 16;
        stored_palette_group_offset = palette_group * 0x982;
        stored_palette_group = (u16*)((u8*)g_map_palette_stored_colors + stored_palette_group_offset);
        while (store_all < 16) {
            stored_palette_group[palette_index + store_all] = g_map_palette_modified_colors[palette_group]
                                                                                           [palette_index + store_all];
            store_all++;
        }
    }
}
