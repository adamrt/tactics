#include "psx/types.h"

extern void world_copy_bytes(void* dst, void* src, s32 len);
extern u8 g_battle_selected_tile_data[];
extern u8 D_8014D038[];
extern u8 D_8014D080[];
extern u8 D_8014D0A0[];

/* Snapshot the AT (active-turn) list and free-cursor state into the four
   caller-owned buffers so the caller can restore them later. */
void battle_copy_at_and_cursor_to(void* at_list, void* cursor_state,
    void* misc_ids, void* turn_header) {
    world_copy_bytes(at_list, D_8014D038, 0x22);
    world_copy_bytes(cursor_state, D_8014D080, 0xE);
    world_copy_bytes(misc_ids, D_8014D0A0, 0x40);
    world_copy_bytes(turn_header, g_battle_selected_tile_data, 0xA);
}
