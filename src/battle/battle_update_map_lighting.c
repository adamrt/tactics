#include "psx/gpu.h"

extern s32 g_map_palette_move_pending;
extern s32 g_map_palette_upload_pending;
extern u32 g_map_palette_upload_words[];

void battle_update_map_lighting(void) {
    RECT rectangle;
    s32* move_pending;

    move_pending = &g_map_palette_move_pending;

    if (*move_pending != 0) {
        rectangle.x = 0;
        rectangle.y = 0x1ee;
        rectangle.w = 0x100;
        rectangle.h = 0xe;
        MoveImage(&rectangle, 0, 0x1e0);
        *move_pending = 0;
    }

    if (g_map_palette_upload_pending != 0) {
        rectangle.x = 0;
        rectangle.y = 0x1ee;
        rectangle.w = 0x100;
        rectangle.h = 0xe;
        LoadImage(&rectangle, g_map_palette_upload_words);
        g_map_palette_upload_pending = 0;
        *move_pending = 1;
    }
}
