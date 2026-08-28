#include "psx/types.h"

extern u8* g_target_current_action;
extern s32 battle_magical_evade_calculation(void);
extern s32 battle_calculate_magic_accuracy_no_elemental(void);
extern void battle_calculate_mp_percent_damage(void);
extern void battle_mp_recovery_routine(void);

/* Formula 0x0F: absorb (Y)% of max MP, hit F(MA+X)%. */
void battle_formula_absorb_mp_y_percent(void) {
    if (battle_magical_evade_calculation() != 0) {
        return;
    }
    if (battle_calculate_magic_accuracy_no_elemental() != 0) {
        return;
    }
    battle_calculate_mp_percent_damage();
    *(u16*)(g_target_current_action + 4) = *(u16*)(g_target_current_action + 8);
    battle_mp_recovery_routine();
}
