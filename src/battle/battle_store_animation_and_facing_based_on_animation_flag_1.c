#include "fft/battle.h"
#include "psx/types.h"

extern void set_partial_tile_color(s32, s32);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void battle_start_ability_charge_animation(battle_misc_data_t* unit);
extern void battle_store_unit_animation_facing(s32 animation, s32 facing, battle_misc_data_t* unit);
extern void battle_clear_at_list_active(void);
extern u8 g_ability_animation_flags[];
extern s32 g_battle_game_state;

void battle_store_animation_and_facing_based_on_animation_flag_1(void) {
    battle_misc_data_t* unit;
    u16 ability;

    set_partial_tile_color(0, 2);
    g_battle_game_state = BATTLE_GAME_STATE_PRE_ATTACK_ANIMATION;
    unit = battle_get_source_unit_misc_data();
    ability = unit->used_ability_id;
    unit->unit_check = 0;
    if (g_ability_animation_flags[ability * 3] != 0) {
        battle_start_ability_charge_animation(unit);
    } else {
        /* facing is read signed (lh) here. */
        battle_store_unit_animation_facing(2, *(s16*)&unit->facing, unit);
    }
    battle_clear_at_list_active();
}
