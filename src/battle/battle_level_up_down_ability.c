#include "psx/types.h"

typedef struct ActionData {
    u8 pad[0x10];
    u16 flags;
} ActionData;

typedef struct TargetUnit {
    u8 pad[0x22];
    u8 level;
} TargetUnit;

extern ActionData* g_target_current_action;
extern TargetUnit* g_target_unit_data;
extern s32 g_battle_action_state;
extern void main_apply_unit_level_growth(TargetUnit*, s32);

s32 battle_level_up_down_ability(void) {
    s32 lv;
    s32 dir;
    u16 flags;

    flags = g_target_current_action->flags;
    if (flags & 0x80) {
        lv = g_target_unit_data->level + 1;
        dir = 0;
        if (lv >= 100) {
            lv = 99;
        }
    } else if (flags & 0x100) {
        lv = g_target_unit_data->level - 1;
        dir = 1;
        if (lv <= 0) {
            lv = 1;
        }
    } else {
        return 0;
    }
    if (g_battle_action_state == 0) {
        g_target_unit_data->level = lv;
        main_apply_unit_level_growth(g_target_unit_data, dir);
    }
    return 1;
}
