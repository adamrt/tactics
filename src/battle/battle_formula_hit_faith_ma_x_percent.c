#include "psx/types.h"

extern s32 battle_magical_evade_calculation(void);
extern s32 battle_calculate_magic_accuracy(void);
extern void func_80187F24(void);

void battle_formula_hit_faith_ma_x_percent(void) {
    if (battle_magical_evade_calculation() == 0) {
        if (battle_calculate_magic_accuracy() == 0) {
            func_80187F24();
        }
    }
}
