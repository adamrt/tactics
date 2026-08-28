#include "fft/battle.h"
#include "fft/data.h"
#include "psx/types.h"

extern party_data_t* main_get_party_data_pointer(s32 slot);
extern void main_initialize_unit_s_job_levels(u8* total_job_points, u8* job_levels);
extern s32 main_calculate_unlocked_jobs(u8* job_levels, s32 gender_flags);
extern void main_store_job_unlock_bitset(u8* destination, s32 bitset);
extern void main_reset_unit_battle_state(battle_stats_t* unit);
extern void initialize_unit_s_battle_data(battle_stats_t* unit, party_data_t* party_unit);
extern void main_transfer_job_s_data_to_unit_s_data(battle_stats_t* unit);
extern void main_enable_unit_s_r_s_m_flags(battle_stats_t* unit);
extern void calculate_actual_stats(battle_stats_t* unit, s32 arg1);
extern void main_equippable_item_setting(battle_stats_t* unit);
extern void main_equipment_move_jump_x_name_storing_generation(battle_stats_t* unit);

/* Wiki: "Battle Initialization Flag?"; only ever stored from the caller's
 * argument here and in main_unit_battle_initialization. */
extern s32 D_80066200;

s32 main_initialize_unit_s_job_data(battle_stats_t* unit, s32 slot, s32 flag) {
    party_data_t* party_unit;
    u8* job_levels;

    D_80066200 = flag;
    party_unit = main_get_party_data_pointer(slot);
    if (party_unit == 0) {
        return -1;
    }
    if (party_unit->party_id == 0xff) {
        return -1;
    }
    job_levels = party_unit->job_levels;
    main_initialize_unit_s_job_levels(party_unit->total_job_points, job_levels);
    main_store_job_unlock_bitset(party_unit->unlocked_jobs,
        main_calculate_unlocked_jobs(job_levels, party_unit->gender_flags));
    main_reset_unit_battle_state(unit);
    unit->formation_index = slot;
    initialize_unit_s_battle_data(unit, party_unit);
    main_transfer_job_s_data_to_unit_s_data(unit);
    main_enable_unit_s_r_s_m_flags(unit);
    calculate_actual_stats(unit, 0);
    main_equippable_item_setting(unit);
    main_equipment_move_jump_x_name_storing_generation(unit);
    return 0;
}
