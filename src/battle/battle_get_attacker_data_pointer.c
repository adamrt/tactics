#include "psx/types.h"

extern s16 g_selected_unit_index;
extern void get_battle_stats_pointer(s16 unit_id);

void battle_get_attacker_data_pointer(void) {
    get_battle_stats_pointer(g_selected_unit_index);
}
