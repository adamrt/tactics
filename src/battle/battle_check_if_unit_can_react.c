#include "psx/types.h"

extern s32 g_battle_action_type;
extern s32 main_unit_has_status_in_set(const void* unit, u32 status_set_index);

s32 battle_check_if_unit_can_react(const void* unit) {
    if (g_battle_action_type != 0) {
        return 1;
    }
    return main_unit_has_status_in_set(unit, 4);
}
