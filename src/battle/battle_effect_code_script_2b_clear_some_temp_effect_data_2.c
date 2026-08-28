#include "psx/types.h"

extern void battle_clear_temp_effect_data_2(void);

s32 battle_effect_code_script_2b_clear_some_temp_effect_data_2(u16* effect) {
    battle_clear_temp_effect_data_2();
    effect[3] += 2;
    return 1;
}
