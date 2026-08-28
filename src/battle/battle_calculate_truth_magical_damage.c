#include "psx/types.h"

extern s32 battle_calculate_elemental_xa_times_ya(void);
extern void battle_apply_elemental_absorption_and_status(void);
extern void battle_apply_elemental_strengthen(void);
extern void battle_apply_magical_support_status_compatibility(void);

void battle_calculate_truth_magical_damage(void) {
    battle_apply_elemental_strengthen();
    battle_apply_magical_support_status_compatibility();
    if (battle_calculate_elemental_xa_times_ya() == 0) {
        battle_apply_elemental_absorption_and_status();
    }
}
