#include "psx/types.h"

extern s32 g_bunit_ability_type;
extern u16 g_bunit_ability_entries[];

s32 bunit_is_non_action_ability_unlearned(s32 index) {
    s32 result;

    result = 0;
    if (g_bunit_ability_type != 0) {
        result = (g_bunit_ability_entries[index] >> 14) != 0;
    }
    return result;
}
