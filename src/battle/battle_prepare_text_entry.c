#include "psx/types.h"

extern u8* g_battle_text_pointers[32];
extern u8* find_text_id_location(u8* text_section, u32 entry_id);

u8* battle_prepare_text_entry(u32 text_id) {
    u32 entry_id;

    entry_id = text_id;
    return find_text_id_location(g_battle_text_pointers[(entry_id & 0xf800) >> 11],
        entry_id & 0x07ff);
}
