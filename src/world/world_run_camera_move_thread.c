#include "psx/types.h"

void world_switch_to_next_thread(void);
s32 battle_is_battle_camera_active(void);

void world_run_camera_move_thread(void) {
    do {
        world_switch_to_next_thread();
    } while (battle_is_battle_camera_active() != 0);
}
