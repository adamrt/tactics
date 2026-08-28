#include "psx/types.h"

extern s32 g_active_graphics_buffer_index;
extern u8 g_open_otags[];
extern s32 g_open_primitive_count;
extern void ClearOTagR(u32* ot, s32 count);

void open_clear_current_otag(void) {
    volatile u32 stack_padding[2];

    ClearOTagR((u32*)(g_open_otags + g_active_graphics_buffer_index * 0x40), 0x10);
    g_open_primitive_count = 0;
}
