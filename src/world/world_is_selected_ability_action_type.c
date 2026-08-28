#include "psx/types.h"

extern s32 g_world_selected_ability_type;

s32 world_is_selected_ability_action_type(void) {
    return g_world_selected_ability_type == 0;
}
