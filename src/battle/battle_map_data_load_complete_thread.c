#include "psx/types.h"

extern void switch_to_next_thread(void);
extern void battle_mark_map_data_load_complete(void);
extern void battle_stop_current_thread(void);

void battle_map_data_load_complete_thread(void) {
    switch_to_next_thread();
    battle_mark_map_data_load_complete();
    switch_to_next_thread();
    battle_stop_current_thread();
}
