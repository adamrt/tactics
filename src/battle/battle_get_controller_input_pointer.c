#include "psx/types.h"

extern u8 g_battle_event_input[];
extern u8 g_battle_event_current_input[];

u8* battle_get_controller_input_pointer(s32 use_current) {
    u8* result = g_battle_event_input;
    if (use_current != 0) {
        result = g_battle_event_current_input;
    }
    return result;
}
