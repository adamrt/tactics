#include "psx/types.h"

extern s16 g_jobstts_ability_category;

s32 jobstts_is_action_tab(void) {
    return g_jobstts_ability_category == 0;
}
