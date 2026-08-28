#include "psx/types.h"

extern s32 g_world_menu_input_repeat_counter_0;

s32 world_get_menu_input_repeat_counter(void) {
    return g_world_menu_input_repeat_counter_0;
}
