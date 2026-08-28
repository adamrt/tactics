#include "fft/battle.h"
#include "psx/types.h"

extern void main_clear_byte_data(u8* dst, s32 size);
extern void r_s_m_flag_setting(battle_stats_t* unit, u16 ability_id);

/* Rebuilds the unit's learned reaction/support/movement bitfields
 * (0x8b..0x95) from its four innate abilities and its equipped R/S/M
 * abilities. */
void main_enable_unit_s_r_s_m_flags(battle_stats_t* unit) {
    s32 i;
    u8* walk;

    main_clear_byte_data(unit->reaction_abilities, 0xB);
    i = 0;
    /* The original walks innate_abilities[0..3] with a byte pointer that
     * starts at the unit base and keeps the +0x0a in the load. */
    walk = (u8*)unit;
    do {
        r_s_m_flag_setting(unit, ((battle_stats_t*)walk)->innate_abilities[0]);
        walk += 2;
        i += 1;
    } while (i < 4);
    r_s_m_flag_setting(unit, unit->reaction_ability);
    r_s_m_flag_setting(unit, unit->support_ability);
    r_s_m_flag_setting(unit, unit->movement_ability);
}
