#include "psx/types.h"

enum {
    MAP_PALETTE_GROUP_COUNT = 14,
    MAP_PALETTE_GROUP_BYTES = 0x982,
    MAP_PALETTE_ANIMATION_COUNT = 16,
    MAP_PALETTE_ANIMATION_BYTES = 8,
};

extern s32 g_map_palette_upload_pending;
extern s32 g_map_palette_move_pending;
extern u8 D_800995f4[];
extern u8 g_map_palette_updates_disabled[];
extern u8 g_map_palette_animation_states[];
extern u8 D_8009967a[];
extern u8 D_800a1b10;
extern u8 D_800a1b14;
extern u8 D_800a1b50;
extern u8 D_800a1b54;
extern u8 D_8009a8f8;
extern u8 D_8009b27a;
extern u8 D_8009bbfc;
extern u8 D_8009d882;
extern void battle_reset_map_texture_animations(void);

void battle_initialize_map_palette_state(void) {
    s32 group_offset;
    s32 group_end;
    s32 group_enabled;
    s32 animation_offset;
    s32 animation_index;

    g_map_palette_upload_pending = 0;
    g_map_palette_move_pending = 0;

    group_enabled = 1;
    group_offset = 0;
    group_end = MAP_PALETTE_GROUP_COUNT * MAP_PALETTE_GROUP_BYTES;
    do {
        g_map_palette_updates_disabled[group_offset] = 0;
        D_800995f4[group_offset] = group_enabled;

        animation_index = MAP_PALETTE_ANIMATION_COUNT - 1;
        animation_offset = group_offset
            + (MAP_PALETTE_ANIMATION_COUNT - 1)
                * MAP_PALETTE_ANIMATION_BYTES;
        do {
            g_map_palette_animation_states[animation_offset] = 0;
            animation_index--;
            animation_offset -= MAP_PALETTE_ANIMATION_BYTES;
        } while (animation_index >= 0);

        D_8009967a[group_offset] = 0;
        group_offset += MAP_PALETTE_GROUP_BYTES;
    } while (group_offset < group_end);

    D_800a1b10 = 0;
    D_800a1b14 = 0;
    D_800a1b50 = 0;
    D_800a1b54 = 0;
    D_8009a8f8 = 0;
    D_8009b27a = 0;
    D_8009bbfc = 0;
    D_8009d882 = 0;
    battle_reset_map_texture_animations();
}
