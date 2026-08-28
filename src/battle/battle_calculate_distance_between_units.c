#include "fft/battle.h"

s32 battle_calculate_distance_between_units(battle_stats_t* a, battle_stats_t* b) {
    s32 dx = a->x - b->x;
    s32 dy = a->position.bits.y - b->position.bits.y;
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    return dx + dy;
}
