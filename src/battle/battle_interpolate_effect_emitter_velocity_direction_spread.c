#include "fft/battle.h"
extern s32 battle_lerp_and_store(s32, s32, s32, s32*);
void battle_interpolate_effect_emitter_velocity_direction_spread(u8* source, s32 factor, s32* out) {
    battle_lerp_and_store(*(s16*)(source + 0x38), *(s16*)(source + 0x3E), factor, out);
    battle_lerp_and_store(*(s16*)(source + 0x3A), *(s16*)(source + 0x40), factor, out + 1);
    battle_lerp_and_store(*(s16*)(source + 0x3C), *(s16*)(source + 0x42), factor, out + 2);
}
