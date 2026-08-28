#include "psx/types.h"

extern u8 g_card_selected_slot;
extern s32 card_status(s32 slot);
extern s32 card_poll_hardware_event_result(void);

s32 card_wait_for_hardware_event_result(void) {
    s32 result;
    s32 ready;

    while (1) {
        ready = card_status(g_card_selected_slot) & 1;
        result = card_poll_hardware_event_result();
        if (result >= 0)
            return result;
        if (ready != 0)
            return 2;
    }
}
