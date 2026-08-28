#include "psx/types.h"

extern s8 g_equip_menu_thread_running;
extern s16 D_801CF034;
extern u8 g_equip_idle_thread_stop_pending;
extern u8 g_equip_queued_sound_effect_id;
extern u8 g_equip_screen_state;
extern s16 D_801E90EC;
extern s32 g_equip_help_message_id;
extern void* g_menu_descriptor;

extern s32 is_event_thread_running(s32 thread);
extern void initialize_event_thread(s32 thread, void* function);
extern void battle_store_thread_function_parameters(s32 thread, void* descriptor,
    s32 arg2, s32 arg3);
extern void battle_mark_thread_as_stopped(s32 thread);
extern void equip_run_menu_thread(void);
extern void equip_thread_menu_idle_loop(void);
extern s32 equip_set_menu_index_1(s32 index, s32 value);
extern void equip_reset_selection_indices(void);
extern s32 func_801C4490(void);
extern s32 func_801C4A10(void);
extern s32 func_801C4F98(void);

void equip_update_screen_state(void) {
    s32 result;
    s32 state;
    s32 mode;
    s16* descriptor;
    s16* value_ptr;

    if (g_equip_menu_thread_running == 0) {
        if (is_event_thread_running(5) == 0) {
            descriptor = &D_801CF034;
            *descriptor = 0;
            g_menu_descriptor = (u8*)descriptor - 0x38;
            initialize_event_thread(5, equip_run_menu_thread);
            battle_store_thread_function_parameters(5, g_menu_descriptor, 0, 0);
            g_equip_idle_thread_stop_pending = 0;
            g_equip_menu_thread_running = 1;
        }
    }
    if (g_equip_idle_thread_stop_pending != 0) {
        battle_mark_thread_as_stopped(4);
        g_equip_idle_thread_stop_pending = 0;
    }
    state = g_equip_screen_state;
    if (state == 1) {
        value_ptr = &D_801E90EC;
        mode = *value_ptr;
        g_equip_help_message_id = D_801CF034 + 0x1029;
        if (mode == 1) {
            g_equip_queued_sound_effect_id = 5;
        } else {
            if (mode == -1) {
                goto check;
            }
            initialize_event_thread(4, equip_thread_menu_idle_loop);
            g_equip_screen_state = *(u8*)value_ptr + 2;
            equip_set_menu_index_1(0, 0);
            equip_set_menu_index_1(1, 0);
            equip_set_menu_index_1(2, 0);
        }
        equip_reset_selection_indices();
    check:
        g_equip_menu_thread_running = is_event_thread_running(5);
        if (g_equip_menu_thread_running == 0) {
            g_equip_screen_state = 0xFF;
        }
        return;
    }
    switch (state) {
    case 2:
        result = func_801C4490();
        break;
    case 4:
        result = func_801C4A10();
        break;
    case 5:
        result = func_801C4F98();
        break;
    }
    if (result == 0) {
        g_equip_screen_state = 1;
        g_equip_idle_thread_stop_pending = 1;
    }
}
