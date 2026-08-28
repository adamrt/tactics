#include "psx/types.h"

extern s32 battle_check_thread_running_status(s32);
extern s32 battle_stop_current_thread(void);

s32 battle_get_next_available_thread_id(s32 arg0) {
    s32 i;

    if (arg0 < 0x10) {
        return arg0;
    }
    i = 1;
    do {
        if (battle_check_thread_running_status(i) == 0) {
            return i;
        }
        i++;
    } while (i < 0x10);
    return battle_stop_current_thread();
}
