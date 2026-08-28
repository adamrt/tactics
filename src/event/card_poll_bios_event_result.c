#include "psx/types.h"

extern s32 TestEvent(s32 event);
extern s32 g_card_bios_event_done;
extern s32 g_card_bios_event_write_error;
extern s32 g_card_bios_event_busy;
extern s32 g_card_bios_event_eject;
extern void card_consume_bios_events(void);

s32 card_poll_bios_event_result(void) {
    s32 result = -1;
    if (TestEvent(g_card_bios_event_done) == 1)
        result = 0;
    else if (TestEvent(g_card_bios_event_write_error) == 1)
        result = 1;
    else if (TestEvent(g_card_bios_event_busy) == 1)
        result = 2;
    else if (TestEvent(g_card_bios_event_eject) == 1)
        result = 3;
    if (result != -1)
        card_consume_bios_events();
    return result;
}
