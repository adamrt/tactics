#include "psx/types.h"

extern s32 g_battle_at_list_active;

void battle_clear_at_list_active(void) {
    g_battle_at_list_active = 0;
}
