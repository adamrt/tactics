#include "psx/types.h"

extern void battle_set_thread_task_id(s32 task_id);
extern void battle_setup_open_companion_executable(s32 id);
extern void func_801CA664(void);

void battle_open_companion_executable_6(void) {
    battle_set_thread_task_id(0x36);
    battle_setup_open_companion_executable(6);
    func_801CA664();
}
