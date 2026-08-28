#include "psx/types.h"

extern void world_set_thread_task_id(s32 task_id);
extern void func_800F218C(void);
extern void world_stop_current_thread(void);

void world_func_800f21ec(void) {
    world_set_thread_task_id(0x41);
    func_800F218C();
    world_stop_current_thread();
}
