#include "psx/types.h"

extern u8 g_battle_disabled_texture_window[8];
extern void world_copy_bytes(void* destination, const void* source, s32 count);

void battle_set_menu_disabled_texture_window(u8* menu) {
    *(s16*)(menu + 0x1C) = 0;
    *(s16*)(menu + 0x26) = 0;
    world_copy_bytes(menu + 0x20, g_battle_disabled_texture_window, 8);
}
