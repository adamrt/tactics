#include "psx/types.h"

extern u8* g_battle_text_pointers[32];
extern u8* g_battle_text_pointer_backup[32];
extern s32 g_battle_text_pointer_backup_active;
extern void world_copy_bytes(void* destination, const void* source, s32 count);

void battle_save_text_pointer_table(void) {
    if (g_battle_text_pointer_backup_active == 0) {
        world_copy_bytes(g_battle_text_pointer_backup, g_battle_text_pointers, 0x80);
        g_battle_text_pointer_backup_active++;
    }
}
