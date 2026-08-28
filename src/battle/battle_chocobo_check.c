#include "fft/battle.h"
#include "psx/types.h"

extern s32 func_8005E1B0(battle_stats_t* unit, s32 x);

s32 battle_chocobo_check(battle_stats_t* unit) {
    if ((u32)(unit->job_id - 0x5E) >= 3U)
        return 0;
    if (func_8005E1B0(unit, 0xA) != 0)
        return 0;
    if (unit->mount_info != 0)
        return 2;
    return 1;
}
