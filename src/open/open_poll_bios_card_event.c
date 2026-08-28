#include "psx/types.h"

extern s32 TestEvent(s32 event);
extern s32 g_card_bios_event_done;
extern s32 g_card_bios_event_write_error;
extern s32 g_card_bios_event_busy;
extern s32 g_card_bios_event_eject;
extern void open_consume_bios_card_events(void);

s32 open_poll_bios_card_event(void) {
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
        open_consume_bios_card_events();
    return result;
}
