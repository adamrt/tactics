#include "fft/battle.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32, s32);
extern s32* battle_get_selected_ability_address(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u16);
extern void learn_ability_on_hit_2(battle_stats_t*);
extern void learn_ability_on_hit_setup(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void battle_call_set_animation_based_on_status(battle_misc_data_t*);
extern void battle_post_command_update_animation_display(battle_misc_data_t*);
extern s32 g_controller_input_copy_1;
extern u16 g_post_action_unit_id;
extern s32 g_post_action_display_phase;
extern s32 g_post_action;
extern s32 g_animation_continue_check;

void battle_handle_learn_ability_on_hit_state(void) {
    s32* selected_ability_address;
    s32 selected_ability;
    s32 counter;
    s32 skip_animation;
    s32 hit_count;
    battle_misc_data_t* casting_unit;
    battle_misc_data_t* target_unit;
    u8 compiler_stack_pad[8];

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    selected_ability_address = battle_get_selected_ability_address();
    casting_unit = battle_get_casting_unit_misc_data();
    selected_ability = *selected_ability_address;
    switch (selected_ability) {
    case 7:
        if (g_post_action_display_phase == 2) {
            target_unit = battle_get_unit_misc_data_by_battle_id(g_post_action_unit_id);
            learn_ability_on_hit_2(target_unit->battle_data);
        }
    case 8:
    case 0xff:
        g_post_action_display_phase += 1;
        if (g_post_action_display_phase >= 3) {
            g_post_action = 1;
        } else {
            learn_ability_on_hit_setup();
        }
        break;
    }
    if (g_post_action != 0 && g_animation_continue_check == 0) {
        counter = 0;
        if (casting_unit->numeric_display_active == 0) {
            hit_count = casting_unit->target_count;
            skip_animation = 0;
            if (hit_count > 0) {
                do {
                    target_unit = battle_get_unit_misc_data_by_battle_id(
                        casting_unit->target_list[counter]);
                    /* Keeps the counter increment after the call's delay
                     * slot; GCC otherwise hoists it into the slot. */
                    asm volatile("" : : : "memory");
                    counter += 1;
                    if (target_unit != 0 && target_unit->numeric_display_active != 0) {
                        skip_animation = 1;
                        break;
                    }
                    hit_count = casting_unit->target_count;
                } while (counter < hit_count);
            }
            if (skip_animation == 0) {
                casting_unit = battle_get_source_unit_misc_data();
                battle_call_set_animation_based_on_status(casting_unit);
                battle_post_command_update_animation_display(casting_unit);
            }
        }
    }
}
