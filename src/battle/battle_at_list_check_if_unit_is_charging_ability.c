#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_at_list_id;
extern s32 battle_calculate_at_list_and_get_specific_unit_id(s32);
extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(s32);
extern void battle_x_y_data_gathering_for_attacks(battle_misc_data_t*);
extern void func_8017AAF8(u8*);
extern void set_partial_tile_color(s32, s32);
extern void battle_move_cursor_to_unit(battle_misc_data_t*);
extern void battle_increment_at_list_id(void);

void battle_at_list_check_if_unit_is_charging_ability(void) {
    s32 id;
    battle_misc_data_t* unit;

loop:
    id = battle_calculate_at_list_and_get_specific_unit_id(g_battle_at_list_id);
    if (id >= 0) {
        unit = battle_get_unit_misc_data_by_battle_id(id & 0xFF);
        if ((id & 0x100) != 0) {
            battle_x_y_data_gathering_for_attacks(unit);
            func_8017AAF8(&unit->battle_data->action_actor_id);
            set_partial_tile_color(7, 3);
        } else {
            battle_move_cursor_to_unit(unit);
            set_partial_tile_color(0, 0);
        }
    } else {
        battle_increment_at_list_id();
        goto loop;
    }
    battle_increment_at_list_id();
}
