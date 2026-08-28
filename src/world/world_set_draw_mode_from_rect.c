#include "psx/types.h"

extern s32 GetTPage(s32, s32, s16, s16);
extern void SetDrawMode(void*, s32, s32, s32, void*);
extern u8 g_world_texture_window[];

/* Set a WORLD draw mode from aligned texture-page coordinates in a rect. */
void world_set_draw_mode_from_rect(void* mode, const u16* rect) {
    SetDrawMode(mode, 0, 0,
        GetTPage(0, 0, (s16)(rect[0] & 0xffc0),
            (s16)(rect[1] & 0xff00))
            & 0xffff,
        g_world_texture_window);
}
