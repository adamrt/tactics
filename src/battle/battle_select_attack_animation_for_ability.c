#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_spritesheet_data[];
extern u8 g_ability_animation_flags[];
extern void battle_select_weapon_attack_animation(battle_misc_data_t* attacker, battle_misc_data_t* target);
extern void battle_select_item_ability_animation(battle_misc_data_t* attacker, battle_misc_data_t* target);
extern void battle_store_unit_animation_facing(s32 animation, s32 facing, battle_misc_data_t* unit);

void battle_select_attack_animation_for_ability(battle_misc_data_t* attacker, battle_misc_data_t* target) {
    s32 animation;
    s32 sequence_id;

    sequence_id = g_spritesheet_data[attacker->spritesheet_id * 4 + 1];
    if (sequence_id < 8) {
        if (sequence_id >= 5) {
            /* facing is loaded signed (lh) here. */
            battle_store_unit_animation_facing(0x2c, *(s16*)&attacker->facing,
                attacker);
            return;
        }
    }

    animation = g_ability_animation_flags[attacker->used_ability_id * 3 + 1];
    if (animation == 0) {
        battle_select_weapon_attack_animation(attacker, target);
        return;
    }
    if (animation == 1) {
        battle_select_item_ability_animation(attacker, target);
        return;
    }
    battle_store_unit_animation_facing(animation, *(s16*)&attacker->facing, attacker);
}
