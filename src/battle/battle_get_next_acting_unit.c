#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_game_state;

extern void battle_stop_game_flow(void);
extern s32 battle_calculate_at_list_and_get_specific_unit_id(s32);
extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(s32);
extern void battle_x_y_data_gathering_for_attacks(battle_misc_data_t*);
extern void func_8017AAF8(s32);
extern void set_partial_tile_color(s32, s32);
extern void battle_move_cursor_to_unit(battle_misc_data_t*);
extern void battle_store_name_and_data_of_unit_selected_by_cursor(void);
extern void set_at_list_active(void);

void battle_get_next_acting_unit(s32 arg) {
    s32 id;
    battle_misc_data_t* unit;

    battle_stop_game_flow();
    g_battle_game_state = 10;
    id = battle_calculate_at_list_and_get_specific_unit_id(arg);
    if (id >= 0) {
        unit = battle_get_unit_misc_data_by_battle_id(id & 0xFF);
        if ((id & 0x100) != 0) {
            battle_x_y_data_gathering_for_attacks(unit);
            func_8017AAF8((s32)&unit->battle_data->action_actor_id);
            set_partial_tile_color(7, 3);
        } else {
            battle_move_cursor_to_unit(unit);
            set_partial_tile_color(0, 0);
        }
    }
    battle_store_name_and_data_of_unit_selected_by_cursor();
    set_at_list_active();
}
