#include "psx/types.h"

typedef struct OpenRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} OpenRect;

extern void PutDrawEnv(void* environment);
extern void PutDispEnv(void* environment);
extern void ClearImage(OpenRect* rect, s32 red, s32 green, s32 blue);
extern void MoveImage(OpenRect* rect, s32 x, s32 y);
extern void LoadImage(OpenRect* rect, const void* source);
extern void SetDispMask(s32 enabled);

extern s32 g_open_display_buffer_index;
extern u8 g_open_screen_environments[];
extern volatile u32 g_open_runtime_flags;
extern void* g_open_file_destination;

void open_present_movie_frame(void) {
    OpenRect image_rect;
    OpenRect move_rect;
    s32 display_index;
    u32 flags;

    display_index = g_open_display_buffer_index ^ 1;
    g_open_display_buffer_index = display_index;
    PutDrawEnv(g_open_screen_environments + display_index * 112);

    display_index = g_open_display_buffer_index;
    PutDispEnv(g_open_screen_environments + 0x5c + display_index * 112);

    flags = g_open_runtime_flags;
    if ((flags & 2) == 0) {
        image_rect.h = 240;
        image_rect.x = 0;
        if ((flags & 0x1000) != 0) {
            image_rect.w = 320;
        } else {
            image_rect.w = 256;
        }
        if ((g_open_display_buffer_index & 1) != 0) {
            image_rect.y = 240;
        } else {
            image_rect.y = 0;
        }

        flags = g_open_runtime_flags;
        if ((flags & 0x20000) != 0) {
            ClearImage(&image_rect, 0, 0, 0);
        } else if ((flags & 0x40000) != 0) {
            register s32 move_y __asm__("$3") = 256;

            move_rect.x = 512;
            move_rect.w = 512;
            move_rect.y = move_y;
            move_rect.h = 240;
            MoveImage(&move_rect, image_rect.x, image_rect.y);
        } else {
            LoadImage(&image_rect, g_open_file_destination);
        }
    }

    SetDispMask(((g_open_runtime_flags >> 6) ^ 1) & 1);
}
