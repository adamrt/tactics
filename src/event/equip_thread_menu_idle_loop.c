#include "psx/types.h"

extern void func_8014C858(s32 arg0);

void equip_thread_menu_idle_loop(void) {
    for (;;) {
        func_8014C858(1);
    }
}
