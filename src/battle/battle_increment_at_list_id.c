#include "psx/types.h"

extern s32 g_battle_at_list_id;

void battle_increment_at_list_id(void) {
    s32 id = g_battle_at_list_id + 1;

    g_battle_at_list_id = id;
    if (id >= 0x28) {
        g_battle_at_list_id = 0;
    }
}
