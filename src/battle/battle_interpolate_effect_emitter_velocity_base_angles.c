#include "fft/battle.h"
extern s32 battle_lerp_and_store(s32, s32, s32, s32*);
void battle_interpolate_effect_emitter_velocity_base_angles(u8* source, s32 factor, s32* out) {
    battle_lerp_and_store(*(s16*)(source + 0x2C), *(s16*)(source + 0x32), factor, out);
    battle_lerp_and_store(*(s16*)(source + 0x2E), *(s16*)(source + 0x34), factor, out + 1);
    battle_lerp_and_store(*(s16*)(source + 0x30), *(s16*)(source + 0x36), factor, out + 2);
}
