#include "fft/battle.h"

extern battle_display_unit_t* battle_get_unit_misc_data_by_misc_id(u16);
extern void battle_set_bow_hardcoding(battle_display_unit_t*, battle_display_unit_t*);

void battle_call_bow_hardcoding_by_misc_id(u16 attacker_id, u16 target_id) {
    battle_display_unit_t* attacker = battle_get_unit_misc_data_by_misc_id(attacker_id);
    battle_display_unit_t* target = battle_get_unit_misc_data_by_misc_id(target_id);

    battle_set_bow_hardcoding(attacker, target);
}
