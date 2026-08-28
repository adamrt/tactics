#include "psx/types.h"

typedef struct {
    u8 pad00[0x18];
    s32 real_x; /* 0x18 */
    s32 real_z; /* 0x1C */
    s32 real_y; /* 0x20 */
    u8 pad24[0x40 - 0x24];
    s16 screen_x; /* 0x40 */
    s16 screen_z; /* 0x42 */
    s16 screen_y; /* 0x44 */
} ScreenCoordsUnit;

void battle_set_real_coords_from_screen_coords(ScreenCoordsUnit* unit) {
    unit->real_x = unit->screen_x << 12;
    unit->real_z = unit->screen_z << 12;
    unit->real_y = unit->screen_y << 12;
}
