#include "psx/types.h"

extern s32 g_world_selected_ability_type;
extern u16 D_801C8594[];

s32 world_is_non_action_ability_unlearned(s32 index) {
    s32 result = 0;

    if (g_world_selected_ability_type != 0) {
        result = (D_801C8594[index] >> 14) != 0;
    }
    return result;
}
