#include "psx/types.h"

extern s32 g_battle_status_flag;
extern s32 g_battle_at_list_id;

void battle_clear_at_list_id_and_flag(void) {
    if (g_battle_status_flag == 0) {
        g_battle_status_flag = 1;
        g_battle_at_list_id = 0;
    }
}
