#include "psx/gpu.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void battle_finish_battle_frame(void);
extern void battle_cleanup_battle_misc_units(void);
extern s32 D_8004597c;
extern u16 g_battle_screen_fade_intensity;
extern u16 g_map_transition_step;
extern s32 g_battle_game_state;
extern s32 D_800960f4;
extern POLY_F4 g_battle_screen_fade_polygons[2];
extern u8 g_battle_screen_fade_draw_modes[];

void battle_handle_map_jumping_out_2_state(void) {
    u32 intensity;
    char unused[24];

    battle_handle_free_cursor_input();
    intensity = g_battle_screen_fade_intensity;
    if (intensity >= 0x100) {
        intensity = 0xff;
    }

    g_battle_screen_fade_polygons[D_8004597c].r0 = intensity;
    g_battle_screen_fade_polygons[D_8004597c].g0 = intensity;
    g_battle_screen_fade_polygons[D_8004597c].b0 = intensity;

    AddPrim(main_get_otag(), &g_battle_screen_fade_polygons[D_8004597c]);
    AddPrim(main_get_otag(), &g_battle_screen_fade_draw_modes[D_8004597c * 0xc]);

    g_battle_screen_fade_intensity += g_map_transition_step;
    if ((s16)g_battle_screen_fade_intensity >= 0x102) {
        g_battle_screen_fade_intensity = 0xff;
        g_battle_game_state = 0x39;
        D_800960f4 = 0;
        battle_finish_battle_frame();
        battle_cleanup_battle_misc_units();
    }
}
