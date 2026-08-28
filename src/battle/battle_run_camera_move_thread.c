#include "psx/types.h"

extern void switch_to_next_thread(void);
extern s32 battle_is_battle_camera_active(void);

void battle_run_camera_move_thread(void) {
    do {
        switch_to_next_thread();
    } while (battle_is_battle_camera_active() != 0);
}
