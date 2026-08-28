#include "psx/types.h"

extern u32 g_open_new_button_presses;
extern u32 g_open_current_button_input;
extern s32 g_open_directional_repeat_initial_delay;
extern s32 g_open_directional_repeat_period;
extern s32 g_open_up_repeat_counter;
extern s32 g_open_down_repeat_counter;
extern s32 g_open_direction_counter_2;
extern s32 g_open_direction_counter_3;

u32 open_check_repeating_directional_input(u32 buttons) {
    s32 next;
    u32 pressed;

    pressed = g_open_new_button_presses;
    pressed &= buttons;
    if (pressed != 0) {
        g_open_direction_counter_3 = 0;
        g_open_direction_counter_2 = 0;
        g_open_down_repeat_counter = 0;
        g_open_up_repeat_counter = 0;
        return pressed;
    }

    if ((buttons & 0x1000) != 0) {
        if ((g_open_current_button_input & 0x1000) != 0) {
            s32* up_counter = &g_open_up_repeat_counter;

            if (g_open_directional_repeat_initial_delay < (*up_counter = next = *up_counter + 1)) {
                *up_counter = next - g_open_directional_repeat_period;
                return 0x1000;
            }
        } else {
            g_open_up_repeat_counter = 0;
        }
    }

    if ((buttons & 0x4000) != 0) {
        if ((g_open_current_button_input & 0x4000) != 0) {
            s32* down_counter = &g_open_down_repeat_counter;
            s32 old_counter;
            s32 down_next;

            old_counter = *down_counter;
            if (g_open_directional_repeat_initial_delay < (*down_counter = down_next = old_counter + 1)) {
                old_counter = down_next - g_open_directional_repeat_period;
                *down_counter = old_counter;
                return 0x4000;
            }
        } else {
            g_open_down_repeat_counter = 0;
        }
    }

    return 0;
}
