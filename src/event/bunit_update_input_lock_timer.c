#include "psx/types.h"

extern s32 is_event_thread_running(s32 arg0);
extern s32 bunit_unit_list_needs_scroll(void);
extern u32 D_801CF4C0;
extern u8 g_bunit_input_lock_timer;
extern s16 g_bunit_menu_input_mask;
extern s32 g_bunit_menu_input_repeat_mask;
extern s32 g_bunit_menu_input_active_mask;

void bunit_update_input_lock_timer(void) {
    s32 timer;

    if (is_event_thread_running(7) != 0) {
        timer = 0xA;
    } else if ((D_801CF4C0 & 0x60) != 0) {
        timer = 0xA;
    } else if (bunit_unit_list_needs_scroll() != 0) {
        timer = 0xA;
    } else {
        timer = g_bunit_input_lock_timer;
        if (timer == 0) {
            return;
        }
        timer -= 1;
    }
    g_bunit_input_lock_timer = timer;
    if (g_bunit_input_lock_timer != 0) {
        g_bunit_menu_input_mask = 0;
        g_bunit_menu_input_repeat_mask = 0;
        g_bunit_menu_input_active_mask = 0;
    }
}
