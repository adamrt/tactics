#include "psx/types.h"

extern s32 is_event_thread_running(s32 thread_id);
extern s32 g_event_mode;

/* BUNIT.OUT 001c360c - True while a menu transition (thread 15), event mode, or
 * thread 5 is running; used to gate input processing. */
s32 bunit_is_menu_or_transition_active(void) {
    s32 result = 0;
    if (is_event_thread_running(0xF) || g_event_mode != 0 || (result = 0, is_event_thread_running(5))) {
        result = 1;
    }
    return result;
}
