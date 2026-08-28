typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct BattleMiscMovement {
    u8 _pad00[4];
    u8 entd_id;
    u8 _pad05[0x7a];
    u8 center_tile_offset;
    u8 _pad80[0x18];
    u32 current_move_tile_count;
    u8 final_move_tile_count;
} BattleMiscMovement;

extern void handle_map_rotation_input(void);
extern void battle_call_map_zoom(void);
extern void battle_call_map_tilt(void);
extern BattleMiscMovement* battle_get_casting_unit_misc_data(void);
extern void process_single_unit_movement(BattleMiscMovement* misc_data);
extern void battle_update_display_by_misc_id(u8 misc_id);
extern void open_move_confirm_menu(void);
extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32 g_animation_continue_check;
extern s32 g_controller_input_copy_1;

void battle_handle_unit_moving_state(void) {
    BattleMiscMovement* casting_misc_data;

    handle_map_rotation_input();
    battle_call_map_zoom();
    battle_call_map_tilt();
    casting_misc_data = battle_get_casting_unit_misc_data();
    process_single_unit_movement(casting_misc_data);
    if (casting_misc_data->center_tile_offset == 0 && casting_misc_data->current_move_tile_count >= casting_misc_data->final_move_tile_count && g_animation_continue_check == 0) {
        battle_update_display_by_misc_id(casting_misc_data->entd_id);
        open_move_confirm_menu();
    }
    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
}
