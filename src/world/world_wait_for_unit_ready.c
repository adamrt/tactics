#include "psx/types.h"

extern s32 battle_return_one(s32 misc_id);
extern void world_switch_to_next_thread(void);

void world_wait_for_unit_ready(s32 misc_id) {
    while (battle_return_one(misc_id) == 0) {
        world_switch_to_next_thread();
    }
}
