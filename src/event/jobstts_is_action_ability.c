#include "psx/types.h"

extern s32 g_jobstts_ability_type;

s32 jobstts_is_action_ability(void) {
    return g_jobstts_ability_type == 0;
}
