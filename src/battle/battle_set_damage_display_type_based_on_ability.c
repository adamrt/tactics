#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_animation_speed;
extern s32 g_battle_game_state;
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void func_8017CE44(s32 misc_unit_id, u8* data);
extern void set_thrown_item_graphic_and_palette(u32 item_id,
    battle_misc_data_t* unit);
extern s32 func_801A1814(s32 ability_id);
extern void set_target_coordinates_and_attacker_animation(void);
extern void func_800736D4(s32 ability_id, battle_misc_data_t* unit);

void battle_set_damage_display_type_based_on_ability(void) {
    battle_misc_data_t* misc;
    u16 raw;
    s32 ability;
    s32 target;

    g_animation_speed = 1;
    misc = battle_get_casting_unit_misc_data();
    func_8017CE44(misc->battle_data->misc_unit_id, &misc->action_18c);
    raw = misc->last_attack_id;
    /* The target reads 0x1a6 as a signed halfword. */
    target = *(s16*)&misc->reaction_id_1a6;
    ability = raw & 0xffff;
    misc->used_ability_id = raw;
    set_thrown_item_graphic_and_palette(misc->used_weapon_id, misc);
    if (((target != 0) && (ability != target)) || (ability == 0x200) || (ability == 0) || (func_801A1814(ability) != 0)) {
        set_target_coordinates_and_attacker_animation();
        return;
    }
    g_battle_game_state = BATTLE_GAME_STATE_START_EFFECT_FILE_OPEN;
    func_800736D4(ability, misc);
}
