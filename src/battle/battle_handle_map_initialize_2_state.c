#include "psx/gpu.h"

extern s32 func_8008ea6c(s32 map_id, s32 mode);
extern s32 main_get_otag(void);
extern s32 g_screen_polarity;
extern s32 g_battle_map_id;
extern s32 D_800960f4;
extern s32 g_previous_battle_game_state;
extern s32 g_battle_game_state;
extern u16 g_battle_screen_fade_intensity;
extern POLY_F4 g_battle_screen_fade_polygons[2];
extern u8 g_battle_screen_fade_draw_modes[];

void battle_handle_map_initialize_2_state(void) {
    s32 old_state;
    char unused[24];

    D_800960f4 = func_8008ea6c(g_battle_map_id, D_800960f4);
    g_battle_screen_fade_polygons[g_screen_polarity].r0 = 0xff;
    g_battle_screen_fade_polygons[g_screen_polarity].g0 = 0xff;
    g_battle_screen_fade_polygons[g_screen_polarity].b0 = 0xff;
    AddPrim(main_get_otag(), &g_battle_screen_fade_polygons[g_screen_polarity]);
    AddPrim(main_get_otag(), &g_battle_screen_fade_draw_modes[g_screen_polarity * 0xc]);
    if (D_800960f4 == 0xd) {
        old_state = g_previous_battle_game_state;
        g_previous_battle_game_state = 0;
        g_battle_screen_fade_intensity = 0xff;
        g_battle_game_state = old_state;
    }
}
