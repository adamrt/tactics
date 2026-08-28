#include "psx/types.h"

s32 battle_stop_current_thread(void);
s32 battle_check_thread_running_status(s32);

extern s32 D_80174038;

s32 battle_find_next_inactive_thread(s32 arg0) {
    s32 i;
    s32 result;

    if (arg0 < 0x10) {
        return arg0;
    }
    i = D_80174038 + 1;
    if (i < 0x10) {
        do {
            if (battle_check_thread_running_status(i) == 0) {
                return i;
            }
            i++;
        } while (i < 0x10);
    }
    return battle_stop_current_thread();
}
