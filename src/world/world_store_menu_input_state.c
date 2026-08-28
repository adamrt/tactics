#include "psx/types.h"

typedef struct {
    s32 new_buttons;
    s32 current_buttons;
    s32 previous_buttons;
    s32 repeat_counter_0;
    s32 repeat_counter_1;
    s32 repeat_counter_2;
} WorldMenuInputState;

extern s32 g_world_menu_new_button_input;
extern s32 g_world_menu_current_button_input;
extern s32 g_world_menu_previous_button_input;
extern s32 g_world_menu_input_repeat_counter_0;
extern s32 g_world_menu_input_repeat_counter_1;
extern s32 g_world_menu_input_repeat_counter_2;

/* Copy a six-word WORLD menu-controller state snapshot. */
void world_store_menu_input_state(const WorldMenuInputState* state) {
    g_world_menu_new_button_input = state->new_buttons;
    g_world_menu_current_button_input = state->current_buttons;
    g_world_menu_previous_button_input = state->previous_buttons;
    g_world_menu_input_repeat_counter_0 = state->repeat_counter_0;
    g_world_menu_input_repeat_counter_1 = state->repeat_counter_1;
    g_world_menu_input_repeat_counter_2 = state->repeat_counter_2;
}
