#include "psx/types.h"

extern s32 g_world_text_section_offsets[32];
extern u8* g_world_text_section_pointers[32];

void world_initialize_text_section_pointers(void) {
    s32* offset;
    u8** section;
    s32 i;
    u8* text;
    s32 value;

    offset = g_world_text_section_offsets;
    i = 0;
    text = (u8*)(offset + 32);
    section = g_world_text_section_pointers;
    do {
        value = *offset;
        offset++;
        i++;
        value += (s32)text;
        *section = (u8*)value;
        section++;
    } while (i < 32);
}
