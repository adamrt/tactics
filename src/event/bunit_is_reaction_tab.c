#include "psx/types.h"

extern s16 g_bunit_ability_category;

/* Reaction abilities occupy category one. */
s32 bunit_is_reaction_tab(void) {
    return g_bunit_ability_category == 1;
}
