#include "psx/types.h"

enum {
    MAP_MESH_PALETTE_DATA_BYTES = 0x982,
    MAP_PALETTE_ROW_COUNT = 16,
    MAP_PALETTE_COLORS_PER_ROW = 16,
    MAP_PALETTE_ANIMATION_STATE_BYTES = 8,
};

extern u8 g_map_palette_updates_disabled;
extern u8 g_map_palette_animation_states;
extern s32 g_map_palette_upload_pending;

void battle_extract_palette_colors(
    const u16* palette, s32 mesh_index, s32 palette_row_index);

void battle_load_map_palette_data(
    const u16* palette,
    s32 mesh_index,
    s32 palette_row_index,
    s32 load_all_rows) {
    s32 mesh_offset;
    s32 clear_index;
    s32 row_index;
    s32 clear_offset;
    s32 palette_bank_offset;
    const u16* palette_row;

    mesh_offset = mesh_index * MAP_MESH_PALETTE_DATA_BYTES;
    if (*(&g_map_palette_updates_disabled + mesh_offset) != 0) {
        return;
    }

    palette_bank_offset = mesh_offset;
    if (load_all_rows == 1) {
        clear_index = MAP_PALETTE_ROW_COUNT - 1;
        clear_offset = palette_bank_offset
            + clear_index * MAP_PALETTE_ANIMATION_STATE_BYTES;
        do {
            *(&g_map_palette_animation_states + clear_offset) = 0;
            clear_index--;
            clear_offset -= MAP_PALETTE_ANIMATION_STATE_BYTES;
        } while (clear_index >= 0);

        row_index = 0;
        palette_row = palette;
        do {
            battle_extract_palette_colors(palette_row, mesh_index, row_index);
            row_index++;
            palette_row += MAP_PALETTE_COLORS_PER_ROW;
        } while (row_index < MAP_PALETTE_ROW_COUNT);
    } else {
        *(&g_map_palette_animation_states
            + palette_row_index * MAP_PALETTE_ANIMATION_STATE_BYTES
            + palette_bank_offset) = 0;
        battle_extract_palette_colors(palette, mesh_index, palette_row_index);
    }

    g_map_palette_upload_pending = 1;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
