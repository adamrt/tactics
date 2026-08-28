#include "psx/types.h"

s32 battle_effect_code_script_01_store_next_half_as_new_counter_return_(s16* effect) {
    s32 counter = effect[3];
    s32 base = ((s32*)effect)[2];
    effect[3] = *(u16*)(counter + base + 2);
    return 1;
}
