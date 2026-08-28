#include "fft/battle.h"
#include "psx/types.h"

extern void main_clear_byte_data(u8*, s32);

void main_initialize_status_ct(battle_stats_t* unit) {
    main_clear_byte_data(unit->status_ct, 16);
    if ((unit->team_flags & 4) || (unit->unit_flags & 9)) {
        unit->death_counter = 0xff;
    } else {
        unit->death_counter = 3;
    }
}
