#include "fft/battle.h"

extern s32 battle_lerp_and_store(s32 start, s32 end, s32 factor, s32* out);

void battle_interpolate_effect_emitter_spawn_position(u8* source, s32 factor, s32* out) {
    battle_lerp_and_store(*(s16*)(source + 0x14), *(s16*)(source + 0x1A), factor, out);
    battle_lerp_and_store(*(s16*)(source + 0x16), *(s16*)(source + 0x1C), factor, out + 1);
    battle_lerp_and_store(*(s16*)(source + 0x18), *(s16*)(source + 0x1E), factor, out + 2);
}
