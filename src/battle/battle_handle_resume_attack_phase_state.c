#include "fft/battle.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32, s32);
extern s32* battle_get_selected_ability_address(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern s32 battle_resume_attack_phase_control(void);
extern void set_damage_display_type(void);
extern void main_game_free(void*);
extern void set_sp2_entd_id_invalid(battle_misc_data_t*);
extern void action_facing_exception_handler(battle_stats_t*, s32);
extern void store_some_acting_unit_data(battle_stats_t*);
extern void battle_call_set_animation_based_on_status(battle_misc_data_t*);
extern void battle_update_anim_display_for_all_targets(battle_misc_data_t*);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern s32 action_phase_control(void);
extern void battle_post_action_xp_jp_ability(void);
extern s32 g_controller_input_copy_1;
extern s32 g_post_action;
extern void* g_sp2_data;
extern s32 g_action_type;
extern s32 g_battle_action_phase;

void battle_handle_resume_attack_phase_state(void) {
    s32 facing;
    battle_stats_t* battle_data;
    s32 selected_ability;
    battle_misc_data_t* unit;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    selected_ability = *battle_get_selected_ability_address();
    if (selected_ability >= 7 && (selected_ability < 9 || selected_ability == 0xff)) {
        g_post_action = 1;
    }
    unit = battle_get_casting_unit_misc_data();
    if (g_post_action != 0 && battle_resume_attack_phase_control() == 0 && unit->numeric_display_active == 0) {
        if (unit->continue_attack != 0) {
            /* 0x1b5: undocumented byte after job_level_for_display. */
            *((u8*)unit + 0x1b5) += 1;
            set_damage_display_type();
            return;
        }
        if (g_sp2_data != 0) {
            main_game_free(g_sp2_data);
            g_sp2_data = 0;
        }
        set_sp2_entd_id_invalid(unit);
        if (g_action_type == 0x100 && g_battle_action_phase == 1) {
            facing = *(s16*)&unit->facing;
            if (facing < 0) {
                facing += 0x3ff;
            }
            facing = (u32)facing >> 10;
            battle_data = unit->battle_data;
            action_facing_exception_handler(battle_data, facing & 0xff);
        }
        store_some_acting_unit_data(unit->battle_data);
        battle_call_set_animation_based_on_status(unit);
        battle_update_anim_display_for_all_targets(unit);
        battle_get_source_unit_misc_data();
        if (g_battle_action_phase != 0) {
            if (g_battle_action_phase != 2) {
                g_battle_action_phase += 1;
            }
            if (action_phase_control() != 0) {
                return;
            }
        }
        battle_post_action_xp_jp_ability();
    }
}
