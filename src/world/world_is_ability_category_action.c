#include "psx/types.h"

extern s16 g_world_ability_category;

s32 world_is_ability_category_action(void) {
    return g_world_ability_category == 0;
}
