#include "psx/types.h"

extern void func_800F67F0(void);
extern s32 world_check_thread_running_status(s32 thread_id);

s32 world_func_800f2d70(void) {
    func_800F67F0();
    return world_check_thread_running_status(6);
}
