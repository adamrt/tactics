#include "fft/battle.h"

u32 main_get_known_abilities(battle_stats_t* unit, u32 skillset_id) {
    u8* flags = (u8*)unit + skillset_id * 3;

    return ((u32)flags[0x99] << 16) + ((u32)flags[0x9a] << 8) | flags[0x9b];
}
