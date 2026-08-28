#include "psx/gpu.h"

extern void battle_handle_free_cursor_input(void);
extern u32 main_get_otag(void);
extern volatile s32 g_gpu_frame_counter;
extern u16 g_battle_screen_fade_intensity;
extern u16 g_map_transition_step;
extern POLY_F4 g_battle_screen_fade_polygons[2];
extern DR_MODE g_battle_screen_fade_draw_modes[];

void battle_handle_close_battle_state(void) {
    u16 intensity;
    /* The original frame reserves this otherwise-unused stack area. */
    volatile u8 stack_padding[0x18];

    battle_handle_free_cursor_input();
    intensity = g_battle_screen_fade_intensity;
    if (intensity >= 0x100) {
        intensity = 0xff;
    }
    g_battle_screen_fade_polygons[g_gpu_frame_counter].r0 = intensity;
    g_battle_screen_fade_polygons[g_gpu_frame_counter].g0 = intensity;
    g_battle_screen_fade_polygons[g_gpu_frame_counter].b0 = intensity;
    AddPrim((void*)main_get_otag(), &g_battle_screen_fade_polygons[g_gpu_frame_counter]);
    AddPrim((void*)main_get_otag(), &g_battle_screen_fade_draw_modes[g_gpu_frame_counter]);
    g_battle_screen_fade_intensity += g_map_transition_step;
}
