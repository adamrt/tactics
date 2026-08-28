#include "fft/battle.h"
#include "psx/types.h"

/* Add, remove, or replace a status-set flag and refresh the unit's current status. */
void main_change_unit_status(battle_stats_t* unit, s32 status_set, u8 status_flag,
    s32 change_type) {
    u8 flag = status_flag;
    u8* set;
    u8 updated;
    u8 current;

    switch (change_type) {
    case 0:
        updated = *((u8*)unit + status_set + 0x1bb) | status_flag;
        break;
    case 1:
        updated = *((u8*)unit + status_set + 0x1bb) & ~status_flag;
        break;
    case 2:
        updated = flag;
        break;
    }

    set = (u8*)unit + status_set;
    current = set[0x4e];
    set[0x1bb] = updated;
    set[0x58] = updated | current;
}
