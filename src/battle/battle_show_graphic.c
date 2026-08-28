#include "psx/types.h"

extern void set_current_thread_task_id(u32);
extern void setup_companion_executable(u32);
extern void func_801C05D4(void);

void battle_show_graphic(void) {
    set_current_thread_task_id(0x3D);
    setup_companion_executable(0xC);
    func_801C05D4();
}
