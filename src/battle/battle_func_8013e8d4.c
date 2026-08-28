#include "psx/types.h"

extern void battle_set_thread_task_id(s32 id);
extern void func_8013E874(void);
extern void battle_stop_current_thread(void);

void battle_func_8013e8d4(void) {
    battle_set_thread_task_id(0x41);
    func_8013E874();
    battle_stop_current_thread();
}
