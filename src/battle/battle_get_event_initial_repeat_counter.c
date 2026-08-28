#include "psx/types.h"

extern u32 g_battle_event_initial_repeat_counter;

u32 battle_get_event_initial_repeat_counter(void) {
    return g_battle_event_initial_repeat_counter;
}
