#include "psx/types.h"

extern s16 g_bunit_ability_category;

/* The action-ability tab is category zero. */
s32 bunit_is_action_tab(void) {
    return g_bunit_ability_category == 0;
}
