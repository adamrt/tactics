#include "psx/types.h"

extern s32 battle_check_thread_running_status(s32 thread_id);
extern u16 D_8016604A;
extern u16 D_80165FF6;

s32 battle_is_menu_still_building(void) {
    s32 i;
    s32 result;

    if (D_8016604A != 0) {
        return D_8016604A;
    }
    if (battle_check_thread_running_status(3) != 0) {
        return 2;
    }
    i = 4;
    do {
        if (i != 3) {
            if (battle_check_thread_running_status(i) != 0) {
                break;
            }
        }
        i += 1;
    } while (i < 0xA);
    if (D_80165FF6 != 1) {
        result = (i != 0xA);
        return result * 4;
    }
    return 2;
}
