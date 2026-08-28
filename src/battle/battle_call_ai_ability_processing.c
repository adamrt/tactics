#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;
extern u8 g_ai_hit_counter;
extern u16 g_ai_total_hit_percent;
extern u8 g_ai_acting_unit_id;
extern u8 g_ai_current_action_base_hit_percent;
extern u8 D_801A0D80;
extern u8 D_801A0D7E;
extern void func_8019DD8C(u8*, s32);

s32 battle_call_ai_ability_processing(u8* p) {
    battle_ai_data_t* ai;
    s32 n;
    s32 cnt;

    g_ai_hit_counter = 0xFF;
    ai = &g_ai_data_base;
    if (p[0] == g_ai_acting_unit_id) {
        n = g_ai_current_action_base_hit_percent;
        D_801A0D80 = 1;
        if (n == 0xFF) {
            g_ai_hit_counter = 0;
            g_ai_total_hit_percent = 0;
            D_801A0D7E = 0;
        }
    }
    func_8019DD8C(p, 0);
    cnt = ai->hit_counter;
    if (cnt != 0xFF) {
        if (ai->valuable_target_hit == 0 || cnt == 0) {
            return 0;
        }
        ai->current_action.base_hit_percent = ai->total_hit_percent / cnt;
    }
    return 1;
}
