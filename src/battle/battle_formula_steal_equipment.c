#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern s32 func_801879C8(void);
extern void battle_nullify_action(void);
extern s32 battle_physical_evade_calculation(void);
extern void battle_store_speed_and_x(void);
extern s32 battle_calculate_physical_status_accuracy(void);
extern void battle_maintenance(void);

/* Formula 0x26: steal equipped item, hit (SP+X)%. */
void battle_formula_steal_equipment(void) {
    battle_action_data_t* action;

    if (func_801879C8() != 0) {
        battle_nullify_action();
        g_target_current_action->miss_type = 7;
        return;
    }
    if (battle_physical_evade_calculation() != 0) {
        return;
    }
    battle_store_speed_and_x();
    if (battle_calculate_physical_status_accuracy() != 0) {
        return;
    }
    battle_maintenance();
    action = g_target_current_action;
    if (action->hit != 0) {
        /* Halfword store: special_effect = 0x10 (Steal Item), special_flags_2 = 0. */
        action->special_effect = 0x10;
    }
}
