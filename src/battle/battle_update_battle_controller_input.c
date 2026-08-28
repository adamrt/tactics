#include "fft/battle.h"

extern u32 main_read_controller_input(s32 port);
extern s32 battle_get_script_variable(s32 variable_id);
extern void battle_filter_battle_controller_input(u32* input);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void main_play_sound(s32 sound_id);
extern void main_game_reset(void);

extern u32 g_controller_input_raw;
extern u32 g_controller_input_previous;
extern u32 g_controller_input_pressed;
extern u32 g_controller_input_released;
extern u32 g_controller_previous_copy_0;
extern u32 g_controller_previous_copy_1;
extern u32 g_controller_previous_copy_2;
extern u32 g_controller_previous_copy_3;
extern u32 g_controller_pressed_copy_0;
extern u32 g_controller_pressed_copy_1;
extern u32 g_controller_pressed_copy_2;
extern u32 g_controller_pressed_copy_3;
extern u32 g_controller_stable_frames;
extern s32 g_battle_game_state;
extern s32 g_battle_status_menu_requested;
extern s32 g_battle_status_menu_enabled;

s32 battle_update_battle_controller_input(void) {
    u32 pressed;
    u32 previous;
    u32 current;
    u32 released;
    battle_misc_data_t* unit;

    g_controller_input_raw = main_read_controller_input(1);
    if (battle_get_script_variable(0x1fc) != 0) {
        battle_filter_battle_controller_input(&g_controller_input_raw);
    }

    pressed = g_controller_input_pressed;
    previous = g_controller_input_previous;
    current = g_controller_input_raw;
    g_controller_pressed_copy_0 = pressed;
    g_controller_pressed_copy_1 = pressed;
    g_controller_pressed_copy_2 = pressed;
    g_controller_pressed_copy_3 = pressed;
    g_controller_input_pressed = ~previous & current;
    released = ~current & previous;
    g_controller_previous_copy_0 = previous;
    g_controller_previous_copy_1 = previous;
    g_controller_previous_copy_2 = previous;
    g_controller_previous_copy_3 = previous;
    g_controller_input_released = released;

    if (previous == current) {
        g_controller_stable_frames++;
    } else {
        g_controller_stable_frames = 0;
    }

    g_controller_input_previous = g_controller_input_raw;
    if ((g_controller_input_pressed & 0x10) != 0 && g_battle_game_state != BATTLE_GAME_STATE_EVENT) {
        unit = battle_get_source_unit_misc_data();
        if (g_battle_status_menu_enabled != 0 && g_battle_status_menu_requested == 0 && (unit->team_flags & 8) == 0) {
            main_play_sound(0x71);
            g_battle_status_menu_requested = 1;
        }
    }

    if ((g_controller_input_previous & 0x90c) == 0x90c) {
        main_game_reset();
    }
    return 1;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
