#include "psx/types.h"

extern s32 battle_check_if_tutorial_event(void);
extern s32 battle_get_script_variable(s32 variable_id);

extern u8 g_battle_input_initial_delay;
extern u8 g_battle_input_repeat_period;
extern u8 g_battle_input_secondary_repeat_period;
extern s32 g_event_speed;
extern u32 g_battle_event_input;
extern u32 g_battle_event_current_input;
extern u32 g_battle_event_previous_input;
extern u32 g_battle_event_initial_repeat_counter;
extern u32 g_battle_event_repeat_counter;
extern u32 g_battle_event_secondary_repeat_counter;

void battle_update_event_input_state(u32 input) {
    u32 filtered_input;
    s32 initial_delay;
    s32 repeat_delay;
    s32 secondary_repeat_delay;
    u32 previous_input;
    u32 counter;

    if (input == 0 || (battle_check_if_tutorial_event() != 0 && (battle_get_script_variable(0x29) & 0x5000) != 0)) {
        g_battle_event_initial_repeat_counter = 0;
        g_battle_event_repeat_counter = 0;
        g_battle_event_secondary_repeat_counter = 0;
    }

    previous_input = g_battle_event_current_input;
    g_battle_event_current_input = input;
    g_battle_event_input = 0;
    g_battle_event_previous_input = previous_input;
    filtered_input = input & 0xf00c;

    if (previous_input != input || filtered_input == 0) {
        g_battle_event_input = ~previous_input & input;
        g_battle_event_initial_repeat_counter = 0;
    } else {
        initial_delay = g_battle_input_initial_delay / g_event_speed;
        counter = ++g_battle_event_initial_repeat_counter;
        if (counter == initial_delay) {
            g_battle_event_input = filtered_input;
        }
        if (counter >= initial_delay) {
            counter = ++g_battle_event_repeat_counter;
            g_battle_event_secondary_repeat_counter++;
            repeat_delay = g_battle_input_repeat_period / g_event_speed;
            if (counter >= repeat_delay) {
                g_battle_event_repeat_counter = 0;
                if ((input & 0x80) != 0) {
                    g_battle_event_input = input & 0xa000;
                } else {
                    g_battle_event_input = input & 0xf000;
                }
            }
            secondary_repeat_delay = g_battle_input_secondary_repeat_period;
            {
                s32 event_speed;
                event_speed = g_event_speed;
                secondary_repeat_delay /= event_speed;
            }
            if (g_battle_event_secondary_repeat_counter >= secondary_repeat_delay) {
                g_battle_event_secondary_repeat_counter = 0;
                if ((g_battle_event_current_input & 0x80) != 0) {
                    g_battle_event_input |= g_battle_event_current_input & 0x500c;
                } else {
                    g_battle_event_input |= g_battle_event_current_input & 0x000c;
                }
            }
        } else {
            g_battle_event_repeat_counter = 0;
            g_battle_event_secondary_repeat_counter = 0;
        }
    }
}
