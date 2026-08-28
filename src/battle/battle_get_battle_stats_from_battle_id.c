#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];

battle_stats_t* battle_get_battle_stats_from_battle_id(u32 id) {
    if (id >= 0x15) {
        return (battle_stats_t*)0;
    }
    return &battle_stats[id];
}
