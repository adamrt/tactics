#include "psx/types.h"

extern s32 D_801CE184;
extern s32 D_801CE1AC;
extern s32 D_801CE1C0;
extern s32 D_801CE198;

/* EQUIP.OUT 001bf590 - Prime the four "menu section dirty" flags before the
 * next redraw pass. */
void equip_reset_menu_state_flags(void) {
    D_801CE184 = 1;
    D_801CE1AC = 1;
    D_801CE1C0 = 1;
    D_801CE198 = 1;
}
