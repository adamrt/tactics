#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_action_state;

extern void main_copy_action_data(u8*, u8*);
extern void main_store_current_status(battle_stats_t*);
extern s32 battle_call_attack_preparation_at_preview(s32);
extern s32 func_8018370C(s32, s32);
extern s32 battle_get_number_of_turns_to_resolve(s32, s32, s32);

s32 battle_at_list_preview(battle_stats_t* unit, s32 arg1, s32 arg2) {
    u8 save[0x18];
    u8* act;
    s32 old_state;
    s32 r;
    u8 old_charged_ability_ct;
    u8 old_inflicted_status;
    u8 old_movement_taken;
    u8 old_action_taken;

    act = &unit->action_actor_id;
    main_copy_action_data(act, save);
    old_charged_ability_ct = unit->charged_ability_ct;
    old_inflicted_status = unit->inflicted_status[0];
    old_movement_taken = unit->movement_taken;
    old_action_taken = unit->action_taken;
    old_state = g_battle_action_state;
    g_battle_action_state = 2;
    if (battle_call_attack_preparation_at_preview(arg1) == 1) {
        unit->charged_ability_ct = 0;
    }
    r = func_8018370C(arg2, 3);
    if (r != -1) {
        r = battle_get_number_of_turns_to_resolve(unit->misc_unit_id,
                unit->charged_ability_ct, arg2)
            & 0xFF;
    }
    g_battle_action_state = old_state;
    unit->movement_taken = old_movement_taken;
    unit->action_taken = old_action_taken;
    unit->inflicted_status[0] = old_inflicted_status;
    main_store_current_status(unit);
    unit->charged_ability_ct = old_charged_ability_ct;
    main_copy_action_data(save, act);
    return r;
}
