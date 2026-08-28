#include "psx/types.h"

extern s32 update_deep_dungeon_map_animation(void);
extern void battle_set_state_after_command(void);

void battle_handle_deep_dungeon_mesh_finish_state(void) {
    if (update_deep_dungeon_map_animation() != 0) {
        battle_set_state_after_command();
    }
}
