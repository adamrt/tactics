#include "psx/gpu.h"
#include "psx/types.h"

extern u32 g_system_flags;
extern u32 g_wldcore_polled_button_input;
extern u32 g_wldcore_previous_button_input;
extern u32 g_wldcore_new_button_presses;
extern u32 g_wldcore_current_button_input;

extern u32 main_read_controller_input(s32 controller);
extern void suzuki_change_volume_balance(s32 volume, s32 balance);
extern void put_sound_type(s16 sound_type);
extern void calculate_change_in_volume(s32 volume, s32 duration);
extern void main_game_reset(void);

void wldcore_reset_game_if_special_keycode_is_pressed(void) {
    u32 input;
    u32 previous;

    g_wldcore_previous_button_input = g_wldcore_polled_button_input;
    input = main_read_controller_input(0);
    g_wldcore_polled_button_input = input;

    if (g_system_flags & 0x4) {
        g_wldcore_new_button_presses = 0;
        g_wldcore_current_button_input = 0;
    } else {
        previous = g_wldcore_previous_button_input;
        g_wldcore_current_button_input = input;
        g_wldcore_new_button_presses = input & ~previous;
    }

    if (g_wldcore_polled_button_input == 0x90c) {
        DrawSync(0);
        suzuki_change_volume_balance(0x3fff, 1);
        put_sound_type(0xc0);
        calculate_change_in_volume(0x74ff, 1);
        main_game_reset();
    }
}
