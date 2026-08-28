#include "psx/types.h"

typedef struct {
    u8 pad00[0x18];
    s32 x; /* 0x18 */
    s32 y; /* 0x1C */
    s32 z; /* 0x20 */
    u8 pad24[0x40 - 0x24];
    s16 sx; /* 0x40 */
    s16 sy; /* 0x42 */
    s16 sz; /* 0x44 */
} ScreenCoords;

void battle_set_screen_coords_from_real_coords(ScreenCoords* p) {
    p->sx = p->x / 4096;
    p->sy = p->y / 4096;
    p->sz = p->z / 4096;
}
