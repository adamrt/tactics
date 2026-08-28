#include "psx/types.h"

extern s32 g_selected_ability;

s32* battle_get_selected_ability_address(void) {
    return &g_selected_ability;
}
