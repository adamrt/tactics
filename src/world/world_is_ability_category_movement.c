#include "psx/types.h"

extern s16 g_world_ability_category;

/* Sibling of world_is_ability_category_action (category 0). */
s32 world_is_ability_category_movement(void) {
    return g_world_ability_category == 3;
}
