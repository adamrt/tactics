#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void battle_check_if_all_unit_facing_needs_changed(void);
extern s32 func_8017E7E4(u8 arg0, u8* arg1);
extern void battle_prep_for_displaying_earned_exp_jp(battle_misc_data_t* arg0);
extern void battle_move_cursor_to_unit(battle_misc_data_t* arg0);
extern void learn_ability_on_hit_setup(void);
extern s32 D_80096204;
extern s32 g_post_action;
extern s32 g_animation_continue_check;

void battle_post_action_xp_jp_ability(void) {
    battle_misc_data_t* unit;
    battle_stats_t* stats;

    unit = battle_get_source_unit_misc_data();
    battle_check_if_all_unit_facing_needs_changed();
    if (unit != 0) {
        stats = unit->battle_data;
        if (stats != 0 && func_8017E7E4(stats->misc_unit_id, &unit->earned_experience) == -1) {
            unit->job_level_for_display = 0;
            unit->level_for_display = 0;
            unit->earned_jp = 0;
            unit->earned_experience = 0;
        }
    }
    battle_prep_for_displaying_earned_exp_jp(unit);
    D_80096204 = 0;
    battle_move_cursor_to_unit(unit);
    learn_ability_on_hit_setup();
    g_post_action = 0;
    g_animation_continue_check = 0;
}
