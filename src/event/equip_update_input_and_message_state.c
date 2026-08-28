#include "psx/types.h"

extern u8 g_equip_text_thread_running_state;
extern u8 g_equip_input_lock_timer;
extern u32 g_equip_input_primary_repeat;
extern u16 g_equip_input_newly_pressed;
extern u32 g_equip_input_secondary_repeat;
extern u16 g_equip_message_thread_active;
extern s32 g_event_mode;
extern u8 g_equip_suppress_queued_sound;
extern u8 g_equip_queued_sound_effect_id;
extern void func_801C9164(void);
extern s32 equip_get_transition_frame(void);
extern void equip_reset_input_state(void);
extern s32 is_event_thread_running(s32 arg0);

void equip_update_input_and_message_state(void) {
    s32 running;
    s32 frame;
    u8 state;
    s32 delay;

    running = 0;
    func_801C9164();
    frame = equip_get_transition_frame();
    if (frame >= 1 && frame <= 3) {
        equip_reset_input_state();
    } else {
        running = is_event_thread_running(1);
        if (running != 0) {
            equip_reset_input_state();
            if (g_equip_text_thread_running_state != 0) {
                state = 2;
            } else {
                state = 1;
            }
            g_equip_text_thread_running_state = state;
        } else {
            g_equip_text_thread_running_state = 0;
        }
    }

    delay = g_equip_input_lock_timer;
    if (delay != 0) {
        g_equip_input_lock_timer = delay - 1;
        g_equip_input_primary_repeat &= -2;
        g_equip_input_secondary_repeat &= -2;
        g_equip_input_newly_pressed &= -2;
    }
    if (g_equip_input_primary_repeat != 0) {
        g_equip_input_lock_timer = 5;
    }
    if (running == 0) {
        g_equip_message_thread_active = 0;
        g_event_mode = 0;
        g_equip_suppress_queued_sound = 0;
    }
    if (g_equip_text_thread_running_state == 1) {
        g_equip_queued_sound_effect_id = 0x12;
    }
}
