#include "psx/types.h"

extern void func_801851C4(void);
extern void battle_transparent_calculation(void);
extern void battle_abandon_calculation(void);
extern void battle_evasion_changes_due_to_statuses(void);
extern void battle_calculate_hit(void);

void battle_magical_evade_calculation(void) {
    func_801851C4();
    battle_transparent_calculation();
    battle_abandon_calculation();
    battle_evasion_changes_due_to_statuses();
    battle_calculate_hit();
}
