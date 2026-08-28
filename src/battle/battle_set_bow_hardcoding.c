#include "fft/battle.h"

extern void weapon_hit_sound_select(battle_display_unit_t* attacker, s32 hit);
extern void set_target_anim_from_attack_type(battle_display_unit_t* attacker, battle_display_unit_t* target);
extern s32 battle_jump_to_post_action_display(u16 misc_id);
extern void set_evade_and_element_effect(battle_display_unit_t* attacker, s32 bow_attack);

void battle_set_bow_hardcoding(battle_display_unit_t* attacker, battle_display_unit_t* target) {
    if ((attacker != 0) && (target != 0)) {
        weapon_hit_sound_select(attacker, 1);
        set_target_anim_from_attack_type(attacker, target);
        battle_jump_to_post_action_display(target->unit_id);
        set_evade_and_element_effect(attacker, 1);
    }
}
