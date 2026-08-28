#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];

/* Whether the unit has learned the given ability bit of a skillset: returns 1
 * for monsters (every ability known) and for skillsets the unit does not own.
 * Job skillsets 5..0x17 map to learned_abilities rows 0..0x12; the unit's own
 * primary or base-job skillset maps to row 0. */
s32 battle_load_known_ability_flag(s32 unit_id, s32 skillset_id, s32 bit) {
    battle_stats_t* unit = &battle_stats[unit_id];
    s32 byte;
    u8* row;

    if ((unit->unit_flags & 0x20) != 0) {
        return 1;
    }
    if ((u32)(skillset_id - 5) < 0x13) {
        skillset_id = skillset_id - 5;
        goto compute;
    }
    if (skillset_id == unit->primary_skillset) {
        skillset_id = 0;
        goto compute;
    }
    if (skillset_id == unit->base_job_skillset) {
        skillset_id = 0;
        goto compute;
    }
    return 1;
compute:
    row = (u8*)(skillset_id * 3 + (u32)unit + 0x99);
    byte = bit / 8;
    return (row[byte] & (0x80 >> (bit - (byte * 8)))) != 0;
}
