#include "psx/types.h"

extern void world_set_menu_transition_active_flag(void);
extern void world_bin_load_file(s32 file_id);
extern void func_80102E78(s32 arg0);

void world_func_800efa0c(void) {
    world_set_menu_transition_active_flag();
    world_bin_load_file(1);
    func_80102E78(1);
}
