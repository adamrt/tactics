#include "psx/types.h"

extern void battle_calculate_relative_camera_offset(const u16* input,
    s16* output, s32 offset);

void battle_calculate_relative_camera_offset_1(const u16* input, s16* output) {
    battle_calculate_relative_camera_offset(input, output, 1);
}
