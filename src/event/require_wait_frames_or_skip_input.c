#include "psx/types.h"

extern void switch_to_next_event_thread(void);
extern u32* battle_get_controller_input_pointer(s32 controller_id);
extern u32* g_require_controller_input;

void require_wait_frames_or_skip_input(s32 frames) {
    volatile s32 reserved_stack_words[2];
    s32 i = 0;
    u32* input;

    if (frames > 0) {
        do {
            switch_to_next_event_thread();
            input = battle_get_controller_input_pointer(0);
            g_require_controller_input = input;
            if ((*input & 0x20) == 0) {
                i++;
                if (i < frames) {
                    continue;
                }
            }
            break;
        } while (1);
    }
}
