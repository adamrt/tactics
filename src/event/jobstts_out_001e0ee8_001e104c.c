#include "psx/types.h"

extern void func_801E0BA8(void);
extern s32 jobstts_get_transition_frame(void);
extern s32 is_event_thread_running(s32 arg0);

extern u8 D_801EFF63;
extern u8 D_801EFF64;
extern u16 g_jobstts_input_newly_pressed;
extern s32 g_jobstts_input_primary_repeat;
extern s32 g_jobstts_input_secondary_repeat;
extern u8 g_jobstts_menu_state;
extern s32 g_event_mode;

void jobstts_out_001e0ee8_001e104c(void) {
    s32 running;
    s32 frame;

    running = 0;
    func_801E0BA8();
    frame = jobstts_get_transition_frame();
    if ((u32)(frame - 1) >= 7) {
        running = is_event_thread_running(1);
        if (running != 0) {
            g_jobstts_input_newly_pressed = 0;
            g_jobstts_input_primary_repeat = 0;
            g_jobstts_input_secondary_repeat = 0;
            D_801EFF63 = (D_801EFF63 != 0) ? 2 : 1;
            goto after;
        }
        if (D_801EFF63 == 0) {
            goto after;
        }
        D_801EFF63 = 0;
    }
    g_jobstts_input_newly_pressed = 0;
    g_jobstts_input_primary_repeat = 0;
    g_jobstts_input_secondary_repeat = 0;

after:
    if (D_801EFF64 != 0) {
        D_801EFF64--;
        g_jobstts_input_primary_repeat &= ~1;
        g_jobstts_input_secondary_repeat &= ~1;
        g_jobstts_input_newly_pressed &= ~1;
    }
    if (g_jobstts_input_primary_repeat != 0) {
        D_801EFF64 = 5;
    }
    if (running == 0) {
        g_event_mode = 0;
    }
    if (D_801EFF63 == 1) {
        g_jobstts_menu_state = 0x12;
    }
}
