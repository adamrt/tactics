#include "psx/types.h"

extern u16 g_world_draw_primitives_immediately;
extern s32* g_world_active_otag_entries;
extern void DrawPrim(s32*);

/* Merge the caller's display word with the active display word. */
void world_draw_or_append_gpu_primitive(s32* word) {
    s32* ptr;
    s32 value;
    s32 active;
    if (g_world_draw_primitives_immediately != 0) {
        DrawPrim(word);
        return;
    }
    ptr = g_world_active_otag_entries;
    value = *word;
    active = *ptr;
    *word = (value & 0xff000000) | (active & 0x00ffffff);
    *ptr = ((*ptr) & 0xff000000) | (((s32)word) & 0x00ffffff);
}
