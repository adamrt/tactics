#include "psx/types.h"

extern u8* g_target_current_action;
extern u8 g_current_ability_used_item_id;
extern u8 g_item_secondary_data_z_value[];
extern void battle_undead_reversal(void);

/* Formula 0x48: heal (Z * 10) HP. */
void battle_formula_heal_z_times_ten(void) {
    *(u16*)(g_target_current_action + 4) = g_item_secondary_data_z_value[g_current_ability_used_item_id * 3] * 10;
    battle_undead_reversal();
}
