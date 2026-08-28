#include "fft/battle.h"

extern s32 battle_lerp_and_store(s32 start, s32 end, s32 factor, s32* out);

void battle_interpolate_effect_emitter_spawn_spread(u8* source, s32 factor, s32* out) {
    battle_lerp_and_store(*(s16*)(source + 0x20), *(s16*)(source + 0x26), factor, out);
    battle_lerp_and_store(*(s16*)(source + 0x22), *(s16*)(source + 0x28), factor, out + 1);
    battle_lerp_and_store(*(s16*)(source + 0x24), *(s16*)(source + 0x2A), factor, out + 2);
}
