#include "fft/battle.h"
#include "fft/data.h"

extern entd_unit_t* g_current_entd_unit;

extern void initialize_unit_battle_data(
    battle_stats_t* unit,
    entd_unit_t* entd_unit,
    s32 initialize_for_battle,
    s32 unused);
extern s32 save_unit_to_party(battle_stats_t* unit, s32 guest_id);

s32 main_initialize_unit(
    entd_encounter_t* entd,
    s32 unit_id,
    s32 guest_id,
    s32 initialize_for_battle) {
    entd_unit_t* entd_unit = &entd->units[unit_id];

    g_current_entd_unit = entd_unit;
    if (entd_unit->sprite_set == 0) {
        return -2;
    }
    {
        battle_stats_t unit;
        battle_stats_t* unit_data = &unit;

        unit_data->misc_unit_id = 0xff;
        unit_data->entd_slot = 0x20;
        unit_data->existence = 1;
        unit_data->formation_index = 0xff;
        initialize_unit_battle_data(unit_data, entd_unit, initialize_for_battle, 0);
        return save_unit_to_party(unit_data, guest_id);
    }
}
