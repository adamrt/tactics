#include "psx/types.h"

extern s32 g_active_graphics_buffer_index;
extern u32 g_open_otags[2][16];

extern void open_clear_current_otag(void);
extern void open_update_fade_overlay_and_link_primitives(u32* otag);

void open_clear_and_render_current_frame(void) {
    open_clear_current_otag();
    open_update_fade_overlay_and_link_primitives(
        g_open_otags[g_active_graphics_buffer_index]);
}
