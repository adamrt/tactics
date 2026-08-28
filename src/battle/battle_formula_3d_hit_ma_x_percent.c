#include "psx/types.h"

extern s32 battle_magical_evade_calculation(void);
extern s32 battle_calculate_magic_accuracy_without_faith(void);
extern void func_80187F24(void);

void battle_formula_3d_hit_ma_x_percent(void) {
    if (battle_magical_evade_calculation() == 0) {
        if (battle_calculate_magic_accuracy_without_faith() == 0) {
            func_80187F24();
        }
    }
}
