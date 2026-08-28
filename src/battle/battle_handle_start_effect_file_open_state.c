#include "psx/types.h"

extern s32 prepare_effect_data(void);
extern void set_target_coordinates_and_attacker_animation(void);
extern void battle_handle_free_cursor_input(void);
extern s32 g_animation_continue_check;

void battle_handle_start_effect_file_open_state(void) {
    if (prepare_effect_data() != 0) {
        g_animation_continue_check = 1;
    } else {
        g_animation_continue_check = 0;
    }
    if (g_animation_continue_check == 0) {
        set_target_coordinates_and_attacker_animation();
    }
    battle_handle_free_cursor_input();
}
