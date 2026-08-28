#include "psx/types.h"

extern s16 g_bunit_ability_category;

/* Movement abilities occupy category three. */
s32 bunit_is_movement_tab(void) {
    return g_bunit_ability_category == 3;
}
