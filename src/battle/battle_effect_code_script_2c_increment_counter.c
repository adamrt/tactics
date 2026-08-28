#include "psx/types.h"

s32 battle_effect_code_script_2c_increment_counter(u16* effect) {
    effect[3] += 2;
    return 1;
}
