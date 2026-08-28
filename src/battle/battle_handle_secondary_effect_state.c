#include "fft/battle.h"

extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void setup_ranged_ability_display(void);
extern void battle_handle_free_cursor_input(void);

void battle_handle_secondary_effect_state(void) {
    battle_misc_data_t* unit;

    unit = battle_get_casting_unit_misc_data();
    unit->unit_check++;
    setup_ranged_ability_display();
    battle_handle_free_cursor_input();
}
