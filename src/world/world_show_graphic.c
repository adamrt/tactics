#include "psx/types.h"

extern void world_set_thread_task_id(s32 task_id);
extern void world_bin_load_file(s32 file_id);
extern void func_801C05D4(void);

void world_show_graphic(void) {
    world_set_thread_task_id(0x3D);
    world_bin_load_file(0xC);
    func_801C05D4();
}
