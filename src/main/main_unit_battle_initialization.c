#include "fft/battle.h"
#include "fft/data.h"
#include "psx/types.h"

/* Wiki: "Battle Initialization Flag?"; stored from the caller's argument. */
extern u32 D_80066200;

extern void main_reset_unit_battle_state(void);
extern s32 entd_data_calculation(battle_stats_t* unit, entd_unit_t* entd);
extern void calculate_unit_jobs_and_skillsets_from_entd(battle_stats_t* unit, entd_unit_t* entd);
extern void calculate_unit_s_abilities(battle_stats_t* unit, entd_unit_t* entd);
extern void main_enable_unit_s_r_s_m_flags(battle_stats_t* unit);
extern void main_generate_unit_raw_stats(battle_stats_t* unit);
extern void main_copy_job_growths_and_multipliers_to_unit(battle_stats_t* unit);
extern void calculate_actual_stats(battle_stats_t* unit, s32 arg1);
extern void main_equippable_item_setting(battle_stats_t* unit);
extern void calculate_store_entd_unit_equipment(battle_stats_t* unit, entd_unit_t* entd);
extern void main_equipment_move_jump_x_name_storing_generation(battle_stats_t* unit);
extern void main_store_ramza_s_name_birthday_zodiac(battle_stats_t* unit);

s32 main_unit_battle_initialization(battle_stats_t* unit, entd_unit_t* entd, u32 flag, s32 kind) {
    D_80066200 = flag;
    /* Wiki (page 00000587): kind 0x82 is "set in one part of code, rest are
     * 0"; it skips the reset and the ENTD calculation. */
    if (kind != 0x82) {
        main_reset_unit_battle_state();
        if (entd_data_calculation(unit, entd) != 0) {
            return -1;
        }
    }
    if (kind == 0) {
        if ((entd->flags & 0x8) != 0) {
            return 0;
        }
        if (entd->sprite_set < 4) {
            /* Byte 4 of the entry, read as a byte (not the u16 birthday). */
            if (((u8*)entd)[4] == 0) {
                return 0;
            }
        }
    }
    calculate_unit_jobs_and_skillsets_from_entd(unit, entd);
    calculate_unit_s_abilities(unit, entd);
    main_enable_unit_s_r_s_m_flags(unit);
    main_generate_unit_raw_stats(unit);
    main_copy_job_growths_and_multipliers_to_unit(unit);
    if (unit->formation_index == 0xFF) {
        unit->formation_index = 0xFE;
    }
    calculate_actual_stats(unit, 0);
    if (unit->formation_index == 0xFE) {
        unit->formation_index = 0xFF;
    }
    main_equippable_item_setting(unit);
    if (kind != 0x82) {
        if (unit->formation_index >= 0x14) {
            calculate_store_entd_unit_equipment(unit, entd);
        }
    }
    main_equipment_move_jump_x_name_storing_generation(unit);
    main_store_ramza_s_name_birthday_zodiac(unit);
    return 0;
}
