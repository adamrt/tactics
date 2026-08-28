#include "psx/types.h"

extern s16 D_8013A36E;
extern void* get_battle_stats_pointer(s32 unit_id);

void* world_get_battle_stats_for_stored_unit(void) {
    return get_battle_stats_pointer(D_8013A36E);
}
