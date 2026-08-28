#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[21];

u8* battle_unit_exists_party_member_check(s32 unit_id) {
    if (unit_id < 0x15) {
        if (battle_stats[unit_id].entd_slot != 0xFF) {
            return &battle_stats[unit_id].action_actor_id;
        }
    }
    return 0;
}
