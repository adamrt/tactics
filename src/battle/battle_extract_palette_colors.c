#include "psx/types.h"

enum {
    MAP_MESH_PALETTE_DATA_BYTES = 0x982,
    MAP_PALETTE_UPLOAD_BANK_BYTES = 0x200,
    MAP_PALETTE_ROW_COLOR_COUNT = 16,
    MAP_PALETTE_COMPONENT_BYTES = 7,
};

extern u8 g_map_palette_components;
extern u8 g_map_palette_upload_words;

void battle_extract_palette_colors(
    const u16* palette, s32 mesh_index, s32 palette_row_index) {
    s32 color_index;
    s32 mesh_offset;
    s32 selected_row;
    s32 i;
    const u16* palette_ptr;
    u16* upload_palette_base;
    u16* upload_palette_bank;
    u16* packed_color_bank;
    u8* component_bank;
    u16 color;
    u8* components;

    selected_row = palette_row_index;
    i = 0;
    mesh_offset = mesh_index * MAP_MESH_PALETTE_DATA_BYTES;
    component_bank = mesh_offset + &g_map_palette_components;
    upload_palette_base = (u16*)&g_map_palette_upload_words;
    upload_palette_bank = upload_palette_base
        + mesh_index * (MAP_PALETTE_UPLOAD_BANK_BYTES / sizeof(u16));
    packed_color_bank = (u16*)(mesh_offset + (&g_map_palette_components + 0x700));
    palette_ptr = palette;
    do {
        /* PlayStation CLUT words use ABBBBBGGGGGRRRRR. */
        color = *palette_ptr++;
        color_index = selected_row << 4;
        color_index += i;
        i++;
        upload_palette_bank[color_index] = color;
        components = &component_bank[color_index * MAP_PALETTE_COMPONENT_BYTES];
        packed_color_bank[color_index] = color;
        components[0] = color & 0x1f;
        components[1] = (color & 0x3e0) >> 5;
        components[2] = (color & 0x7c00) >> 10;
        components[3] = color >> 15;
    } while (i < MAP_PALETTE_ROW_COLOR_COUNT);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
