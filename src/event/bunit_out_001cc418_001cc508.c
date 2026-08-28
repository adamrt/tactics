#include "psx/types.h"

extern void func_801CC090(void);
extern s32 is_event_thread_running(s32 id);
extern void bunit_reset_menu_input_masks(void);
extern s32 bunit_get_fade_state(void);

extern void* D_801ECB68;
extern u8 D_801E346B;
extern s32 g_event_mode;
extern u8 g_bunit_menu_state;

void bunit_out_001cc418_001cc508(void) {
    s32 running;

    func_801CC090();
    running = is_event_thread_running(1);

    if (running != 0 || D_801ECB68 != 0) {
        bunit_reset_menu_input_masks();
        if (running != 0) {
            D_801E346B = (D_801E346B != 0) ? 2 : 1;
        } else {
            D_801E346B = 0;
        }
    } else if (D_801E346B != 0 || bunit_get_fade_state() != 0) {
        D_801E346B = 0;
        bunit_reset_menu_input_masks();
    }

    if (running == 0) {
        g_event_mode = 0;
    }
    if (D_801E346B == 1) {
        g_bunit_menu_state = 0x12;
    }
}
