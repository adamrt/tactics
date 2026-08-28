#include "psx/types.h"

extern void battle_convert_screen_coords_by_rotation(const s16* screen,
    s16* destination,
    s32 modifier);

void battle_convert_screen_coords_modify_by_1(const s16* screen,
    s16* destination) {
    battle_convert_screen_coords_by_rotation(screen, destination, 1);
}
