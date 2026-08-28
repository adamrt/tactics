#include "fft/battle.h"
#include "fft/data.h"
#include "psx/types.h"

extern s32 main_find_party_slot_by_sprite_set(u8 sprite_set);
extern void main_initialize_unit_s_job_data(battle_stats_t* unit, s32 slot, s32 flag);

extern s32 D_80066200;

s32 main_prep_for_initializing_unit_s_job_data(battle_stats_t* unit, entd_unit_t* entd_unit) {
    s32 slot;

    slot = main_find_party_slot_by_sprite_set(entd_unit->sprite_set);
    if (slot != -1) {
        main_initialize_unit_s_job_data(unit, slot, D_80066200);
        /* Wiki (page 00000539): keep the unit's gender byte minus the
         * Join After Event (0x10) and Save Formation (0x01) bits, then take
         * those two bits from the ENTD entry. */
        unit->unit_flags &= 0xEE;
        unit->unit_flags |= entd_unit->flags & 0x11;
        unit->team_flags = entd_unit->battle_flags;
        unit->initial_team_flags = entd_unit->battle_flags;
        return 0;
    }
    return -1;
}
