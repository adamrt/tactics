#include "psx/types.h"

extern void apply_palette_effect_with_position_scaling(
    s32 first, s32 second, s16 third, s16 fourth, s16 fifth);

void battle_apply_scaled_palette_effect(s32 first, s32 second, s16 third,
    s16 fourth, s16 fifth) {
    apply_palette_effect_with_position_scaling(first, second, third, fourth,
        fifth);
}
