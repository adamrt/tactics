#include "psx/gpu.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern s32 g_screen_polarity;
extern s32 g_animation_speed;
extern s32 g_previous_battle_game_state;
extern s32 g_battle_game_state;
extern u16 g_battle_screen_fade_intensity;
extern u16 g_map_transition_step;
extern POLY_F4 g_battle_screen_fade_polygons[2];
extern u8 g_battle_screen_fade_draw_modes[];

void battle_handle_map_jumping_in_state(void) {
    u32 intensity;
    s32 previous_state;
    char unused[24];

    battle_handle_free_cursor_input();
    intensity = g_battle_screen_fade_intensity;
    if (intensity >= 0x100) {
        intensity = 0xff;
    }
    g_battle_screen_fade_polygons[g_screen_polarity].r0 = intensity;
    g_battle_screen_fade_polygons[g_screen_polarity].g0 = intensity;
    g_battle_screen_fade_polygons[g_screen_polarity].b0 = intensity;
    AddPrim(main_get_otag(), &g_battle_screen_fade_polygons[g_screen_polarity]);
    AddPrim(main_get_otag(), &g_battle_screen_fade_draw_modes[g_screen_polarity * 0xc]);
    g_battle_screen_fade_intensity -= g_map_transition_step;
    if ((s16)g_battle_screen_fade_intensity <= 0) {
        previous_state = g_previous_battle_game_state;
        g_battle_screen_fade_intensity = 0;
        g_previous_battle_game_state = 0;
        g_animation_speed = 1;
        g_battle_game_state = previous_state;
    }
}
