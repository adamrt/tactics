#include "psx/types.h"

extern s32 g_event_mode;
extern s32 g_help_menu_open;
extern s32 g_current_event_thread_id;
extern s32 g_battle_thread_task_ids[];
extern s32 battle_get_third_thread_parameter(void);
extern s32 battle_check_thread_running_status(s32 thread_id);

s32 battle_should_close_menu_thread(s32* out_flag) {
    s32 i;

    if (g_event_mode != 0 || g_help_menu_open != 0) {
        *out_flag = 0;
        return 0;
    }
    for (i = 0; i < 16; i++) {
        if (i != g_current_event_thread_id
            && battle_check_thread_running_status(i) != 0
            && *(s32*)((s8*)g_battle_thread_task_ids + (i << 10)) == 3) {
            *out_flag = 0;
            break;
        }
    }
    if (i == 16 && battle_get_third_thread_parameter() != 0) {
        return 1;
    }
    return 0;
}
