#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern battle_ai_data_t g_ai_data_base;

s32 battle_check_if_unit_can_be_targeted_cryst_trea_mount_trans(s32 unit_idx) {
    battle_ai_data_t* ai = &g_ai_data_base;
    battle_stats_t* unit;
    s32 mount;

    unit = &battle_stats[unit_idx];
    if (unit->entd_slot == 0xff) {
        return 1;
    }
    if (*(u16*)&unit->current_status[0] & 0x140) {
        return 1;
    }
    mount = unit->mount_info;
    if (mount & 0x40) {
        return 1;
    }
    if (ai->unit_decisions[unit_idx].enemy_flag == 0) {
        return 0;
    }
    if (unit->current_status[2] & 0x10) {
        if (mount & 0x80) {
            if (battle_stats[mount & 0xf].current_status[2] & 0x10) {
                goto ret0;
            }
            return 1;
        }
        return 1;
    }
    return 0;
ret0:
    return 0;
}
