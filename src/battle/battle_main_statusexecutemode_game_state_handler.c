#include "psx/types.h"

typedef struct MiscData {
    u8 pad0[4];
    u8 misc_id;
    u8 pad5[0x2b7];
    u8 busy;
} MiscData;

extern s32 g_post_action;
extern s32 g_animation_continue_check;
extern s32 g_controller_input_raw;

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32, s32);
extern s32* battle_get_selected_ability_address(void);
extern MiscData* battle_get_source_unit_misc_data(void);
extern void battle_update_display_by_misc_id(u8);
extern void check_between_turn_events(void);

void battle_main_statusexecutemode_game_state_handler(void) {
    s32 id;
    MiscData* m;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_raw);
    id = *battle_get_selected_ability_address();
    if ((id >= 7) && ((id < 9) || (id == 0xFF))) {
        g_post_action = 1;
    }
    if (g_post_action != 0) {
        if (g_animation_continue_check == 0) {
            m = battle_get_source_unit_misc_data();
            if (m->busy == 0) {
                battle_update_display_by_misc_id(m->misc_id);
                check_between_turn_events();
            }
        }
    }
}
