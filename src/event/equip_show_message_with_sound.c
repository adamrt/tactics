#include "psx/types.h"

extern void equip_initialize_event_thread_if_idle(s32, s32, s32, s32);
extern void main_play_sound(s32);
extern s8 g_equip_suppress_queued_sound;
extern s16 g_equip_message_thread_active;
extern s32 g_event_mode;

void equip_show_message_with_sound(s32 arg0, s32 arg1) {
    equip_initialize_event_thread_if_idle(1, 0x2B, arg0, 0);
    g_equip_suppress_queued_sound = 1;
    main_play_sound(arg1);
    g_equip_message_thread_active = 1;
    g_event_mode = 1;
}
