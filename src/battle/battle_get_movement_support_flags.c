#include "fft/battle.h"
#include "psx/types.h"

s32 battle_get_movement_support_flags(battle_stats_t* unit) {
    u8 flags = unit->movement_abilities[1];
    s32 r = (0 - (unit->movement_abilities[0] & 1)) & 0x22;
    if (flags & 0x80)
        r |= 0x42;
    if (flags & 0x40)
        r |= 0x82;
    if (flags & 0x20)
        r |= 0x102;
    return r;
}
