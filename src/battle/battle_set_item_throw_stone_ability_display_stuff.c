#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_game_state;
extern s32 g_animation_speed;

extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void battle_x_y_data_gathering_for_attacks(battle_misc_data_t* unit);
extern s32 func_801A1814(s32 ability);
extern s32 battle_check_if_ability_is_item_ability(s32 ability);
extern void battle_play_effect(void);
extern void func_80044128(void);
extern void battle_clear_at_list_active(void);

void battle_set_item_throw_stone_ability_display_stuff(void) {
    battle_misc_data_t* unit;
    s32 ability;

    g_battle_game_state = BATTLE_GAME_STATE_ACTION_EXECUTE;
    unit = battle_get_casting_unit_misc_data();
    ability = unit->used_ability_id;
    unit->unit_check = 0;
    battle_x_y_data_gathering_for_attacks(unit);

    if ((ability == 0) || (ability == 0x200)) {
        g_animation_speed = 1;
        battle_clear_at_list_active();
        return;
    }
    if (func_801A1814(ability) != 0) {
        g_animation_speed = 1;
        battle_clear_at_list_active();
        return;
    }
    if ((ability == 0x92) || ((u32)(ability - 0x196) < 8)) {
        if (battle_check_if_ability_is_item_ability(ability) != 0) {
            g_animation_speed = 1;
            battle_clear_at_list_active();
            return;
        }
        battle_play_effect();
        g_animation_speed = 1;
        battle_clear_at_list_active();
        return;
    }
    if ((battle_check_if_ability_is_item_ability(ability) == 0) || ((unit->encoded_animation >> 1) == 0x39)) {
        battle_play_effect();
    }
    func_80044128();
    g_animation_speed = 2;
    battle_clear_at_list_active();
}
