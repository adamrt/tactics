#include "psx/types.h"

extern s32 g_battle_action_type;
extern s32 g_battle_acting_unit_id;
extern u8 D_8019387C;

void battle_store_8019837c_if_not_reacting(s32 arg0, s8 arg1) {
    if (g_battle_action_type == 0 && arg0 == g_battle_acting_unit_id) {
        D_8019387C = arg1;
    }
}
