#include "fft/battle.h"

extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void update_all_unit_rotation_and_vectors(void);
extern void battle_update_and_animate_units(void);
extern void render_wait_direction_unit(void);
extern void update_status_bubbles_and_graphics(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern void handle_map_rotation_input(void);
extern void battle_call_map_zoom(void);
extern void battle_call_map_tilt(void);
extern void end_turn(u8 unit_id);
extern void battle_update_mount_animation_display(battle_misc_data_t* unit);
extern void main_play_sound(s32 sound_id);
extern void check_between_turn_events(void);
extern void battle_set_state_after_command(void);
extern s32 get_facing_input(s32 mode);
extern void battle_decide_facing_direction(battle_misc_data_t* unit, s32 facing);
extern battle_misc_data_t* get_unit_misc_data(u8 misc_id);
extern s32 g_status_screen_selected;
extern s32 g_controller_input_copy_1;
extern s32 g_controller_input;
extern s32 g_current_facing_direction;

void battle_handle_wait_direction_state(void) {
    s32 facing;
    s32 facing_hint;
    u16 frame_data;
    battle_misc_data_t* unit;
    battle_misc_data_t* mounted_unit;

    unit = battle_get_source_unit_misc_data();
    update_all_unit_rotation_and_vectors();
    if (g_status_screen_selected != 1) {
        battle_update_and_animate_units();
    }
    if ((unit->team_flags & 8) != 0) {
        render_wait_direction_unit();
    }
    update_status_bubbles_and_graphics();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    if ((unit->team_flags & 8) != 0) {
        handle_map_rotation_input();
        battle_call_map_zoom();
        battle_call_map_tilt();
        if ((g_controller_input & 0x20) != 0) {
            if (unit->battle_data != 0) {
                end_turn(unit->battle_data->misc_unit_id);
                battle_update_mount_animation_display(unit);
            }
            main_play_sound(1);
            check_between_turn_events();
        } else if ((g_controller_input & 0x40) != 0) {
            battle_set_state_after_command();
        }
        facing = get_facing_input(1);
        if (facing != -1 && facing != g_current_facing_direction) {
            main_play_sound(3);
            g_current_facing_direction = facing;
        }
        battle_decide_facing_direction(unit, facing);
        if (unit->mount_rider_value != 0) {
            mounted_unit = get_unit_misc_data(unit->mount_rider_id);
            if (mounted_unit != 0) {
                battle_decide_facing_direction(mounted_unit, facing);
            }
        }
    } else {
        facing_hint = unit->facing_hint;
        if (facing_hint < 4) {
            battle_decide_facing_direction(unit, facing_hint << 10);
            if (unit->mount_rider_value != 0) {
                mounted_unit = get_unit_misc_data(unit->mount_rider_id);
                if (mounted_unit != 0) {
                    battle_decide_facing_direction(
                        mounted_unit, unit->facing_hint << 10);
                }
            }
        }
        frame_data = unit->unit_check++;
        if (frame_data >= 0x1f) {
            if (unit->battle_data != 0) {
                end_turn(unit->battle_data->misc_unit_id);
                battle_update_mount_animation_display(unit);
            }
            check_between_turn_events();
        }
    }
}
