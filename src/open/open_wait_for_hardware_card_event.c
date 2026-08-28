#include "psx/types.h"

extern s32 card_status(s32 slot);
extern s32 open_poll_hardware_card_event(void);
extern u8 g_open_card_slot;

s32 open_wait_for_hardware_card_event(void) {
    s32 card_ready;
    s32 event_result;

    do {
        card_ready = card_status(g_open_card_slot) & 1;
        event_result = open_poll_hardware_card_event();
        if (event_result >= 0) {
            return event_result;
        }
    } while (card_ready == 0);

    return 2;
}
