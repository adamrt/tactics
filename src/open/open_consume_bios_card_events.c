#include "psx/types.h"

extern s32 TestEvent(s32 event);
extern s32 g_card_bios_event_done;
extern s32 g_card_bios_event_write_error;
extern s32 g_card_bios_event_busy;
extern s32 g_card_bios_event_eject;

void open_consume_bios_card_events(void) {
    TestEvent(g_card_bios_event_done);
    TestEvent(g_card_bios_event_write_error);
    TestEvent(g_card_bios_event_busy);
    TestEvent(g_card_bios_event_eject);
}
