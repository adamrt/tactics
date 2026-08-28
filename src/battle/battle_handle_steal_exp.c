#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_action_state;
extern s32 g_battle_acting_unit_id;
extern u8 D_8019390C;

extern s32 main_check_unit_level_up(battle_stats_t*);

void battle_handle_steal_exp(battle_stats_t* unit, u8 amount) {
    s32 t;
    u8 u;
    s16 s;

    if (g_battle_action_state != 0) {
        return;
    }
    if ((amount & 0x80) == 0) {
        t = unit->experience + amount;
        u = t;
        if (t >= 0x100) {
            u = 0xFF;
        }
        unit->experience = u;
        if (main_check_unit_level_up(unit) != 0) {
            if (unit->misc_unit_id == g_battle_acting_unit_id) {
                D_8019390C = 1;
            }
        }
    } else {
        s = unit->experience - (amount & 0x7F);
        if (s < 0) {
            s = 0;
        }
        unit->experience = s;
    }
}
