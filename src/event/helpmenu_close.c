#include "psx/types.h"

extern void world_copy_bytes(void* destination, const void* source, u32 size);
extern void main_game_free(void* allocation);
extern void stop_current_event_thread(void);

extern u8* g_battle_text_pointers[32];
extern u8* g_helpmenu_saved_text_pointers[32];
extern void* g_high_overlay_load_address;
extern s32 g_help_menu_open;

void helpmenu_close(void) {
    world_copy_bytes(g_battle_text_pointers, g_helpmenu_saved_text_pointers, 0x80);
    main_game_free(g_high_overlay_load_address);
    g_help_menu_open = 0;
    stop_current_event_thread();
}
