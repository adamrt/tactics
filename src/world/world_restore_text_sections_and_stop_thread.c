#include "psx/types.h"

extern void world_copy_bytes(void* destination, const void* source, u32 size);
extern void main_game_free(void* allocation);
extern void world_stop_current_thread(void);

extern u8* g_world_text_section_pointers[32];
extern u8* g_world_text_section_pointer_backup[32];
extern void* g_high_overlay_load_address;
extern s32 g_world_text_overlay_active;

void world_restore_text_sections_and_stop_thread(void) {
    world_copy_bytes(g_world_text_section_pointers, g_world_text_section_pointer_backup,
        sizeof(g_world_text_section_pointers));
    main_game_free(g_high_overlay_load_address);
    g_world_text_overlay_active = 0;
    world_stop_current_thread();
}
