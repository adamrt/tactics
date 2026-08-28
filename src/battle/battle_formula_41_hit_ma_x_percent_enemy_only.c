#include "psx/types.h"

extern u8* g_current_target;
extern u8* g_current_attacker;
extern s32 battle_calculate_magic_accuracy_without_faith(void);
extern void battle_force_attack_miss(void);
extern void func_80187F24(void);

/* Formula 0x41: hit (MA+X)%; forced miss when caster and target share a team. */
void battle_formula_41_hit_ma_x_percent_enemy_only(void) {
    if (battle_calculate_magic_accuracy_without_faith() == 0) {
        if ((*(u16*)(g_current_target + 8) & 0xf000) == (*(u16*)(g_current_attacker + 8) & 0xf000)) {
            battle_force_attack_miss();
        } else {
            func_80187F24();
        }
    }
}
