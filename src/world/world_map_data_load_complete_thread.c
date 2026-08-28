#include "psx/types.h"

extern void world_switch_to_next_thread(void);
extern void battle_mark_map_data_load_complete(void);
extern void world_stop_current_thread(void);

void world_map_data_load_complete_thread(void) {
    world_switch_to_next_thread();
    battle_mark_map_data_load_complete();
    world_switch_to_next_thread();
    world_stop_current_thread();
}
