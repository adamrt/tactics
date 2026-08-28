#include "psx/types.h"

extern void battle_palette_modification(
    s32 first, s32 second, s32 third, s32 palette_index, s32 fifth,
    s32 sixth, s32 seventh, s32 eighth);

void battle_color_field(s32 first, s32 second, s16 red, s16 green, s16 blue) {
    battle_palette_modification(first, second, 0, 0, 1, red, green, blue);
}
