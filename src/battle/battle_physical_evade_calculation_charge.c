#include "psx/types.h"

extern void func_80184F9C(void);
extern void battle_concentrate_calculation(void);
extern void battle_dark_confuse_caclulation(void);
extern void battle_abandon_calculation(void);
extern void battle_evasion_changes_due_to_statuses(void);
extern void func_801854FC(void);
extern void battle_calculate_hit(void);

void battle_physical_evade_calculation_charge(void) {
    func_80184F9C();
    battle_concentrate_calculation();
    battle_dark_confuse_caclulation();
    battle_abandon_calculation();
    battle_evasion_changes_due_to_statuses();
    func_801854FC();
    battle_calculate_hit();
}
