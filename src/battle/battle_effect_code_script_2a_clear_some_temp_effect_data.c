#include "psx/types.h"

extern void battle_clear_temp_effect_data(void* data, s16 value);

s32 battle_effect_code_script_2a_clear_some_temp_effect_data(u16* effect) {
    battle_clear_temp_effect_data(effect, 0);
    effect[3] += 2;
    return 1;
}
