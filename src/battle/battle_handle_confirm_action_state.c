#include "fft/battle.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32, s32);
extern s32* battle_get_selected_ability_address(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern battle_misc_data_t* battle_get_misc_data_at_map_coords_2(s32, s32, s32);
extern void save_3_u16(void*, s32, s32, s32);
extern void store_animation_and_facing(void);
extern void set_partial_tile_color(s32, s32);
extern void battle_set_target_boxes_red(void);
extern s32 g_controller_input_copy_1;
extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_z;
extern s32 g_battle_cursor_y;

void battle_handle_confirm_action_state(void) {
    /* Pin: unpinned (either declaration order) GCC puts the selected-ability
     * pointer in $s0 and the unit in $s1, the reverse of the target. */
    register battle_misc_data_t* unit asm("$16");
    s32* selected_ability_address;
    battle_misc_data_t* target;
    s32 selected_ability;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    selected_ability_address = battle_get_selected_ability_address();
    unit = battle_get_source_unit_misc_data();
    if ((unit->team_flags & 8) != 0) {
        selected_ability = *selected_ability_address;
        switch (selected_ability) {
        /* 0x166/0x167 (target type / target battle id) share the facing_hint
         * word with the WAIT_DIRECTION state; the header keeps the word. */
        case 5:
            *((u8*)unit + 0x166) = *selected_ability_address;
            goto save_target;
        case 6:
        case 7:
            target = battle_get_misc_data_at_map_coords_2(
                g_battle_cursor_x, g_battle_cursor_y, g_battle_cursor_z);
            if (target != 0) {
                *((u8*)unit + 0x166) = *selected_ability_address;
                *((u8*)unit + 0x167) = target->battle_data->misc_unit_id;
            } else {
                *((u8*)unit + 0x166) = 5;
            }
        save_target:
            save_3_u16(&unit->target_panel_x, g_battle_cursor_x,
                g_battle_cursor_z, g_battle_cursor_y);
            store_animation_and_facing();
            return;
        case 8:
        case 0xff:
            set_partial_tile_color(0, 3);
            battle_set_target_boxes_red();
            return;
        default:
            break;
        }
    } else {
        selected_ability = *selected_ability_address;
        switch (selected_ability) {
        case 5:
        case 6:
        case 7:
            store_animation_and_facing();
            return;
        case 8:
        case 0xff:
            set_partial_tile_color(0, 3);
            battle_set_target_boxes_red();
            return;
        default:
            break;
        }
    }
}
