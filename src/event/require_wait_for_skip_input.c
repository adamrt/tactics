#include "psx/types.h"

extern void switch_to_next_event_thread(void);
extern u32* battle_get_controller_input_pointer(s32 controller_id);
extern u32* g_require_controller_input;

void require_wait_for_skip_input(void) {
    u32* input;

    do {
        switch_to_next_event_thread();
        input = battle_get_controller_input_pointer(0);
        g_require_controller_input = input;
    } while ((*input & 0x20) == 0);
}
