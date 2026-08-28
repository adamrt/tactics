#include "psx/types.h"

extern const u8* g_world_text_section_pointers[];
extern const u8* world_get_inner_text(const u8* text, s32 entry_index);

const u8* world_bin_find_text_entry(s32 arg0) {
    return world_get_inner_text(g_world_text_section_pointers[(arg0 & 0xF800) >> 11], arg0 & 0x7FF);
}
