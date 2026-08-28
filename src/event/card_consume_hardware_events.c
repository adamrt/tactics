#include "psx/types.h"

extern s32 TestEvent(s32 event);
extern s32 g_card_hardware_event_done;
extern s32 g_card_hardware_event_error;
extern s32 g_card_hardware_event_busy;
extern s32 g_card_hardware_event_eject;

void card_consume_hardware_events(void) {
    TestEvent(g_card_hardware_event_done);
    TestEvent(g_card_hardware_event_error);
    TestEvent(g_card_hardware_event_busy);
    TestEvent(g_card_hardware_event_eject);
}
