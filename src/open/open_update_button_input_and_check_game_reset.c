#include "psx/gpu.h"
#include "psx/types.h"

extern u32 g_open_runtime_flags;
extern u32 g_open_polled_button_input;
extern u32 g_open_previous_button_input;
extern u32 g_open_new_button_presses;
extern u32 g_open_current_button_input;

extern u32 main_read_controller_input(s32 controller);
extern void suzuki_change_volume_balance(s32 volume, s32 balance);
extern void put_sound_type(s16 sound_type);
extern void open_set_sound_type_and_volume(s32 sound_type, s32 duration);
extern void main_game_reset(void);

void open_update_button_input_and_check_game_reset(void) {
    u32 input;
    u32 previous;

    g_open_previous_button_input = g_open_polled_button_input;
    input = main_read_controller_input(0);
    g_open_polled_button_input = input;

    if (g_open_runtime_flags & 0x10) {
        g_open_new_button_presses = 0;
        g_open_current_button_input = 0;
    } else {
        previous = g_open_previous_button_input;
        g_open_current_button_input = input;
        g_open_new_button_presses = input & ~previous;
    }

    if (!(g_open_runtime_flags & 0x80000) && g_open_polled_button_input == 0x90c) {
        DrawSync(0);
        suzuki_change_volume_balance(0x3fff, 1);
        put_sound_type(0xc0);
        open_set_sound_type_and_volume(0, 1);
        main_game_reset();
    }
}
