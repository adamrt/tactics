#include "psx/types.h"

extern void update_all_unit_rotation_and_vectors(void);
extern void update_status_bubbles_and_graphics(void);
extern void battle_update_and_animate_units(void);
extern void func_8008F130(void);
extern void func_8008F208(void);
extern void battle_tick_real_coord_animation(void);
extern void battle_tick_offset_screen_coord_animation(void);
extern void battle_tick_camera_zoom_animation(void);
extern void battle_tick_camera_rotation_animation(void);
extern s32 g_battle_game_state;
extern s32 g_previous_battle_game_state;
extern s32 g_status_screen_selected;
extern s32 g_animation_continue_check;
extern s32 g_animation_speed;
extern s32 D_8004D958;

void battle_main_effectmode_game_state_handler(void) {
    update_all_unit_rotation_and_vectors();
    if (g_status_screen_selected != 1) {
        battle_update_and_animate_units();
        func_8008F130();
        battle_tick_real_coord_animation();
        battle_tick_offset_screen_coord_animation();
        battle_tick_camera_zoom_animation();
        battle_tick_camera_rotation_animation();
    }
    update_status_bubbles_and_graphics();
    func_8008F208();
    if (g_animation_continue_check == 0) {
        g_battle_game_state = g_previous_battle_game_state;
        g_animation_speed = D_8004D958;
    }
}
