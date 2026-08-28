#include "psx/types.h"

/* Store the four-halfword WORLD graphic rectangle state. */
void world_store_graphic_rect(s16 x, s16 y, s16 width, s16 height) {
    *(s16*)0x801533d0 = x;
    *(s16*)0x801533d2 = y;
    *(s16*)0x801533d4 = width;
    *(s16*)0x801533d6 = height;
}
