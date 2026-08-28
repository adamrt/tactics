#include "psx/types.h"

extern void world_bin_turn_off_unit_status_banner_thread(s32 slot);
extern s32 world_check_thread_running_status(s32 slot);
extern void world_initialize_thread(s32 slot, void* func);
extern void world_store_thread_function_parameters(s32 slot, void* arg, s32 b, s32 c);
extern void func_8010D0CC(void);
extern void D_8018BA2C(void);

void world_bin_toggle_unit_status_banner(s32 enable) {
    if (enable != 0) {
        if (world_check_thread_running_status(8) == 0) {
            world_initialize_thread(8, func_8010D0CC);
            world_store_thread_function_parameters(8, D_8018BA2C, 0, 0);
        }
    } else {
        world_bin_turn_off_unit_status_banner_thread(8);
    }
}
