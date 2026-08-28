#include "fft/battle.h"
#include "psx/types.h"

extern s32 func_8019E5D8(s32 i, s32 arg1);
extern battle_ai_data_t g_ai_data_base;

s32 battle_see_if_any_unit_decided_to_use_an_ability(void) {
    battle_ai_data_t* ai;
    s32 result;
    s32 i;

    result = 0;
    ai = &g_ai_data_base;
    for (i = 0; i < 0x15; i++) {
        if (ai->unit_targetable[i] != 0) {
            if (func_8019E5D8(i, 1) == 1) {
                result = 1;
            } else {
                ai->unit_targetable[i] = 0;
            }
        }
    }
    return result;
}
