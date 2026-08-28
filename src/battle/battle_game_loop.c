#include "fft/battle.h"

extern void poll(void* state);
extern void SetGeomScreen(s32 distance);
extern void VSync(s32 mode);
extern void DrawSync(s32 mode);
extern void process_permanent_sound(void);
extern void tick(u8*, s32, s32);
extern s32 main_get_otag(void);
extern void main_put_otag(void);
extern void battle_process_map_camera_pan(void);
extern void battle_process_map_rotation(void);
extern void process_map_zoom(void);
extern void battle_process_map_tilt(void);
extern void adjust_current_vector_and_real_coords_from_game_state(void);
extern void handle_default_battle_state(void);
extern void battle_handle_free_cursor_help_state(void);
extern void battle_handle_highlight_units_state(void);
extern void battle_handle_open_action_menus_state(void);
extern void handle_idling_action_menus_state(void);
extern void handle_menu_to_targeting_state(void);
extern void battle_handle_action_help_menu_state(void);
extern void battle_handle_display_move_area_state(void);
extern void battle_handle_mini_menu_state(void);
extern void battle_handle_mini_menu_help_state(void);
extern void battle_handle_active_turn_state(void);
extern void battle_handle_unit_move_state(void);
extern void handle_close_move_help_state(void);
extern void battle_handle_move_range_exception_state(void);
extern void battle_handle_illegal_move_menu_state(void);
extern void battle_handle_unit_moving_setup_state(void);
extern void battle_handle_unit_moving_state(void);
extern void battle_handle_move_confirm_menu_state(void);
extern void battle_handle_wait_menu_state(void);
extern void battle_handle_wait_direction_state(void);
extern void handle_crystal_learn_state(void);
extern void battle_handle_action_execute_setup_state(void);
extern void battle_handle_targeting_range_state(void);
extern void battle_handle_illegal_range_state(void);
extern void battle_handle_ability_preview_help_state(void);
extern void battle_handle_ability_preview_state(void);
extern void battle_handle_confirm_action_state(void);
extern void battle_handle_pre_attack_animation_state(void);
extern void battle_handle_action_cast_state(void);
extern void battle_handle_commence_attack_phase_state(void);
extern void battle_handle_effect_damage_display_state(void);
extern void battle_handle_open_sp2_files_state(void);
extern void battle_handle_start_effect_file_open_state(void);
extern void battle_handle_secondary_effect_state(void);
extern void handle_action_execute_state(void);
extern void battle_handle_battle_message_display_state(void);
extern void battle_handle_resume_attack_phase_state(void);
extern void battle_handle_learn_ability_on_hit_state(void);
extern void battle_handle_deep_dungeon_mesh_load_state(void);
extern void battle_handle_deep_dungeon_mesh_finish_state(void);
extern void battle_handle_target_select_start_state(void);
extern void handle_target_select_state(void);
extern void battle_handle_target_select_denied_state(void);
extern void handle_target_select_confirm_state(void);
extern void handle_target_display_start_state(void);
extern void handle_target_display_state(void);
extern void handle_after_command_state(void);
extern void handle_jp_exp_gain_state(void);
extern void handle_change_turn_state(void);
extern void handle_status_execute_state(void);
extern void handle_effect_state(void);
extern void handle_event_state(void);
extern void battle_finish_battle_frame(void);
extern void battle_handle_map_jumping_out_state(void);
extern void battle_handle_map_jumping_out_2_state(void);
extern void battle_handle_close_battle_state(void);
extern void battle_handle_map_initialize_state(void);
extern void battle_handle_map_initialize_2_state(void);
extern void battle_handle_map_jumping_in_state(void);
extern void handle_map_jumping_in_2_state(void);
extern void dispatch_battle_game_state(void);
extern void battle_cleanup_battle_misc_units(void);
extern void update_map_animations();
extern void battle_update_map_lighting(void);
extern s32 battle_frame_sync(s32 base_wait);
extern void update_targeting_movement_tile_colors(void* camera_matrix);
extern void initialize_battle_render_primitives(void);
extern void battle_update_battle_camera_matrices(void* camera_matrix, void* render_buffers,
    void* offset_screen_coords, void* camera_zoom);
extern void initialize_battle_effect_system(void);
extern void battle_initialize_battle_render_state();
extern void battle_prepare_battle_render_frame();
extern s32 battle_process_effect_cycle();
extern void battle_update_battle_controller_input();

extern s32 g_battle_controller_input;
extern s32 g_shifted_controller_flags;
extern s32 g_screen_polarity;
extern s32 g_animation_speed;
extern s32 g_battle_frame_measurement;
extern s32 g_max_battle_frame_measurement;
extern s32 g_frame_pacing_timer;
extern s32 g_frame_pacing_suppressed;
extern s32 g_battle_frame_counter;
extern s32 g_battle_status_menu_enabled;
extern s32 g_battle_game_state;
extern s32 g_animation_continue_check;
extern u8 g_spritesheet_ids_by_vram_slot[];
extern s32 g_game_flow_state;
extern u8 g_battle_camera_matrix[];
/* Base of the two large render-state records; low offsets overlap camera/GPU fields. */
extern u8 g_battle_camera_render_state[];
extern u8 g_battle_offset_screen_coords[];
extern u8 g_battle_camera_zoom[];
extern s32 g_battle_current_real_coords[3];
extern s16 g_battle_camera_integer_coords[3];
extern u8 g_cd_file_state[];

void battle_game_loop(void) {
    u8* timer_field;
    s16* camera_integer;
    s32* camera_fixed;
    s32 frame_measurement;
    s32 empty_timer;
    s32 timer;
    s32 camera_component;
    s32 init_offset;
    s32 i;
    s32 timer_offset;

    initialize_battle_render_primitives();
    battle_initialize_battle_render_state();
    initialize_battle_effect_system();

    init_offset = 0x196b0;
    do {
        g_spritesheet_ids_by_vram_slot[init_offset] = 0;
        init_offset -= 0x32d6;
    } while (init_offset >= 0);

    camera_integer = g_battle_camera_integer_coords;
    camera_fixed = g_battle_current_real_coords;

    do {
        dispatch_battle_game_state();
        g_battle_status_menu_enabled = 0;
        g_battle_controller_input = g_shifted_controller_flags & 7;

    frame_loop:
        battle_update_battle_controller_input();
        battle_prepare_battle_render_frame();
        SetGeomScreen(0x200);
        main_put_otag();
        adjust_current_vector_and_real_coords_from_game_state();

        camera_component = -camera_fixed[0];
        if (camera_component < 0) {
            camera_component += 0xfff;
        }
        camera_integer[0] = camera_component >> 12;
        camera_component = -camera_fixed[1];
        if (camera_component < 0) {
            camera_component += 0xfff;
        }
        camera_integer[1] = camera_component >> 12;
        camera_integer[2] = -camera_fixed[2] / 4096;

        battle_update_battle_camera_matrices(g_battle_camera_matrix, g_battle_camera_render_state,
            g_battle_offset_screen_coords, g_battle_camera_zoom);
        update_targeting_movement_tile_colors(g_battle_camera_matrix);
        if (battle_process_effect_cycle() != 0) {
            g_animation_continue_check = 2;
        } else {
            g_animation_continue_check = 0;
        }

        switch (g_battle_game_state) {
        default:
        case BATTLE_GAME_STATE_FREE_CURSOR:
            handle_default_battle_state();
            break;
        case BATTLE_GAME_STATE_FREE_CURSOR_HELP:
            battle_handle_free_cursor_help_state();
            break;
        case BATTLE_GAME_STATE_HIGHLIGHT_UNITS:
            battle_handle_highlight_units_state();
            break;
        case BATTLE_GAME_STATE_OPEN_ACTION_MENUS:
            battle_handle_open_action_menus_state();
            break;
        case BATTLE_GAME_STATE_IDLING_ACTION_MENUS:
            handle_idling_action_menus_state();
            break;
        case BATTLE_GAME_STATE_MENU_TO_TARGETING:
            handle_menu_to_targeting_state();
            break;
        case BATTLE_GAME_STATE_ACTION_HELP_MENU:
            battle_handle_action_help_menu_state();
            break;
        case BATTLE_GAME_STATE_DISPLAY_MOVE_AREA:
            battle_handle_display_move_area_state();
            break;
        case BATTLE_GAME_STATE_MINI_MENU:
            battle_handle_mini_menu_state();
            break;
        case BATTLE_GAME_STATE_MINI_MENU_HELP:
            battle_handle_mini_menu_help_state();
            break;
        case BATTLE_GAME_STATE_ACTIVE_TURN:
            battle_handle_active_turn_state();
            break;
        case BATTLE_GAME_STATE_AFTER_COMMAND:
            handle_after_command_state();
            break;
        case BATTLE_GAME_STATE_JP_EXP_GAIN:
            handle_jp_exp_gain_state();
            break;
        case BATTLE_GAME_STATE_CHANGE_TURN:
            handle_change_turn_state();
            break;
        case BATTLE_GAME_STATE_STATUS_EXECUTE:
            handle_status_execute_state();
            break;
        case BATTLE_GAME_STATE_UNIT_MOVE:
            battle_handle_unit_move_state();
            break;
        case BATTLE_GAME_STATE_CLOSE_MOVE_HELP:
            handle_close_move_help_state();
            break;
        case BATTLE_GAME_STATE_MOVE_RANGE_EXCEPTION:
            battle_handle_move_range_exception_state();
            break;
        case BATTLE_GAME_STATE_ILLEGAL_MOVE_MENU:
            battle_handle_illegal_move_menu_state();
            break;
        case BATTLE_GAME_STATE_UNIT_MOVING_SETUP:
            battle_handle_unit_moving_setup_state();
            break;
        case BATTLE_GAME_STATE_UNIT_MOVING:
            battle_handle_unit_moving_state();
            break;
        case BATTLE_GAME_STATE_MOVE_CONFIRM_MENU:
            battle_handle_move_confirm_menu_state();
            break;
        case BATTLE_GAME_STATE_WAIT_DIRECTION:
            battle_handle_wait_direction_state();
            break;
        case BATTLE_GAME_STATE_WAIT_MENU:
            battle_handle_wait_menu_state();
            break;
        case BATTLE_GAME_STATE_CRYSTAL_LEARN:
            handle_crystal_learn_state();
            break;
        case BATTLE_GAME_STATE_ACTION_EXECUTE_SETUP:
            battle_handle_action_execute_setup_state();
            break;
        case BATTLE_GAME_STATE_TARGETING_RANGE:
            battle_handle_targeting_range_state();
            break;
        case BATTLE_GAME_STATE_ILLEGAL_RANGE:
            battle_handle_illegal_range_state();
            break;
        case BATTLE_GAME_STATE_ABILITY_PREVIEW_HANDLING:
            battle_handle_ability_preview_state();
            break;
        case BATTLE_GAME_STATE_ABILITY_PREVIEW_HELP:
            battle_handle_ability_preview_help_state();
            break;
        case BATTLE_GAME_STATE_CONFIRM_ACTION:
            battle_handle_confirm_action_state();
            break;
        case BATTLE_GAME_STATE_PRE_ATTACK_ANIMATION:
            battle_handle_pre_attack_animation_state();
            break;
        case BATTLE_GAME_STATE_ACTION_CAST:
            battle_handle_action_cast_state();
            break;
        case BATTLE_GAME_STATE_COMMENCE_ATTACK_PHASE:
            battle_handle_commence_attack_phase_state();
            break;
        case BATTLE_GAME_STATE_EFFECT_DAMAGE_DISPLAY:
            battle_handle_effect_damage_display_state();
            break;
        case BATTLE_GAME_STATE_OPEN_SP2_FILES:
            battle_handle_open_sp2_files_state();
            break;
        case BATTLE_GAME_STATE_START_EFFECT_FILE_OPEN:
            battle_handle_start_effect_file_open_state();
            break;
        case BATTLE_GAME_STATE_SECONDARY_EFFECT:
            battle_handle_secondary_effect_state();
            break;
        case BATTLE_GAME_STATE_ACTION_EXECUTE:
            handle_action_execute_state();
            break;
        case BATTLE_GAME_STATE_BATTLE_MESSAGE_DISPLAY:
            battle_handle_battle_message_display_state();
            break;
        case BATTLE_GAME_STATE_RESUME_ATTACK_PHASE:
            battle_handle_resume_attack_phase_state();
            break;
        case BATTLE_GAME_STATE_LEARN_ABILITY_ON_HIT:
            battle_handle_learn_ability_on_hit_state();
            break;
        case BATTLE_GAME_STATE_DEEP_DUNGEON_MESH_LOAD:
            battle_handle_deep_dungeon_mesh_load_state();
            break;
        case BATTLE_GAME_STATE_DEEP_DUNGEON_MESH_FINISH:
            battle_handle_deep_dungeon_mesh_finish_state();
            break;
        case BATTLE_GAME_STATE_TARGET_SELECT_START:
            battle_handle_target_select_start_state();
            break;
        case BATTLE_GAME_STATE_TARGET_SELECT:
            handle_target_select_state();
            break;
        case BATTLE_GAME_STATE_TARGET_SELECT_DENIED:
            battle_handle_target_select_denied_state();
            break;
        case BATTLE_GAME_STATE_TARGET_SELECT_CONFIRM:
            handle_target_select_confirm_state();
            break;
        case BATTLE_GAME_STATE_TARGET_DISPLAY_START:
            handle_target_display_start_state();
            break;
        case BATTLE_GAME_STATE_TARGET_DISPLAY:
            handle_target_display_state();
            break;
        case BATTLE_GAME_STATE_EFFECT:
            handle_effect_state();
            break;
        case BATTLE_GAME_STATE_EVENT:
            handle_event_state();
            break;
        case BATTLE_GAME_STATE_MAP_JUMPING_OUT:
            battle_handle_map_jumping_out_state();
            break;
        case BATTLE_GAME_STATE_MAP_INITIALIZE:
            battle_handle_map_initialize_state();
            break;
        case BATTLE_GAME_STATE_MAP_JUMPING_IN:
            battle_handle_map_jumping_in_state();
            break;
        case BATTLE_GAME_STATE_MAP_JUMPING_OUT_2:
            battle_handle_map_jumping_out_2_state();
            break;
        case BATTLE_GAME_STATE_MAP_INITIALIZE_2:
            battle_handle_map_initialize_2_state();
            break;
        case BATTLE_GAME_STATE_MAP_JUMPING_IN_2:
            handle_map_jumping_in_2_state();
            break;
        case BATTLE_GAME_STATE_CLOSE_BATTLE:
            battle_handle_close_battle_state();
            break;
        }

        battle_process_map_camera_pan();
        battle_process_map_rotation();
        process_map_zoom();
        battle_process_map_tilt();
        update_map_animations();
        process_permanent_sound();

        if (g_battle_game_state != BATTLE_GAME_STATE_CLOSE_BATTLE) {
            poll(g_cd_file_state);
            g_screen_polarity = !g_screen_polarity;
            g_battle_frame_counter++;
            battle_update_map_lighting();
            frame_measurement = battle_frame_sync(main_get_otag() + 0x5fc);
            g_battle_frame_measurement = frame_measurement;
            i = 0;
            if (g_max_battle_frame_measurement < frame_measurement) {
                g_max_battle_frame_measurement = frame_measurement;
            }
            empty_timer = 0xfe;
            timer_field = g_battle_camera_render_state + 0x40;
            timer_offset = 0;
            do {
                timer = *(s32*)(g_battle_camera_render_state + 0x44 + timer_offset);
                timer_offset += 0x7564;
                if (timer != 0 && timer != empty_timer) {
                    *(s32*)(timer_field + 4) = timer - 1;
                }
                i++;
                timer_field += 0x7564;
            } while (i < 2);

            if (g_battle_game_state == BATTLE_GAME_STATE_EFFECT || g_battle_game_state == BATTLE_GAME_STATE_ACTION_EXECUTE) {
                if (g_animation_speed == 1) {
                    g_frame_pacing_timer = 0;
                } else if (g_frame_pacing_suppressed == 0) {
                    if (g_battle_frame_measurement >= 0x301) {
                        g_frame_pacing_timer = 0x1e;
                    } else if (g_battle_frame_measurement >= 0x201 && g_frame_pacing_timer < 0x0f) {
                        g_frame_pacing_timer = 0x0f;
                    }
                }
            }
            g_frame_pacing_suppressed = 0;
            tick(timer_field, i, empty_timer);
            goto frame_loop;
        }

        battle_finish_battle_frame();
        battle_cleanup_battle_misc_units();
    } while (g_game_flow_state == 0);

    DrawSync(0);
    VSync(0);
    DrawSync(0);
    VSync(0);
}
