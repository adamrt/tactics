#include "psx/types.h"

extern void battle_apply_physical_attack_supports(void);
extern void battle_apply_attacker_berserk_frog(void);
extern void battle_defense_up_routine(void);
extern void battle_target_xa_affecting_statuses(void);
extern void func_80184964(void);

void battle_physical_xa_modifying_statuses_support(void) {
    battle_apply_physical_attack_supports();
    battle_apply_attacker_berserk_frog();
    battle_defense_up_routine();
    battle_target_xa_affecting_statuses();
    func_80184964();
}
