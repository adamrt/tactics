#include "psx/types.h"

extern s16 g_bunit_ability_category;

/* Support abilities occupy category two. */
s32 bunit_is_support_tab(void) {
    return g_bunit_ability_category == 2;
}
