#include "psx/types.h"

extern s32 g_world_text_section_pointers[];

void world_initialize_text_format_section_pointers(s32* arg0) {
    s32 i = 0;
    s32 base = (s32)arg0 + 0x80;
    s32* dst = g_world_text_section_pointers;
    do {
        *dst++ = base + *arg0++;
        i++;
    } while (i < 0x20);
}
