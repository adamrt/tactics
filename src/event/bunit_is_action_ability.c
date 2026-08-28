#include "psx/types.h"

extern s32 g_bunit_ability_type;

/* Action abilities occupy type zero in the ability-pointer classification. */
s32 bunit_is_action_ability(void) {
    return g_bunit_ability_type == 0;
}
