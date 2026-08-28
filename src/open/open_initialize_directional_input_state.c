#include "psx/types.h"

extern u8 g_open_input_initial_delay;
extern u8 g_open_input_repeat_period;
extern s32 g_open_directional_repeat_initial_delay;
extern s32 g_open_directional_repeat_period;
extern s32 g_open_up_repeat_counter;
extern s32 g_open_down_repeat_counter;
extern s32 g_open_direction_counter_2;
extern s32 g_open_direction_counter_3;

void open_initialize_directional_input_state(void) {
    s32 first_limit = g_open_input_initial_delay;
    s32 second_limit = g_open_input_repeat_period;

    g_open_direction_counter_3 = 0;
    g_open_direction_counter_2 = 0;
    g_open_down_repeat_counter = 0;
    g_open_up_repeat_counter = 0;
    g_open_directional_repeat_initial_delay = first_limit;
    g_open_directional_repeat_period = second_limit;
}
