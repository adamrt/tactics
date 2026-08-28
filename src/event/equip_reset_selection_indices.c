#include "psx/types.h"

extern s16 D_801E90F2;

/* EQUIP.OUT 001bf754 - Fill the 4 s16 selection-index slots ending at
 * D_801E90F2 with -1 (writing backwards). */
void equip_reset_selection_indices(void) {
    s16 sentinel = -1;
    s32 remaining = 3;
    s16* slot = &D_801E90F2;
    do {
        *slot = sentinel;
        remaining -= 1;
        slot -= 1;
    } while (remaining >= 0);
}
