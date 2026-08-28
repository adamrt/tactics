#include "psx/types.h"

extern s32 update_deep_dungeon_map_animation(void);
extern void check_between_turn_events(void);

void battle_handle_deep_dungeon_mesh_load_state(void) {
    if (update_deep_dungeon_map_animation() != 0) {
        check_between_turn_events();
    }
}
