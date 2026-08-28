#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_random_process_and_checks_against_r5(s32 a, s32 b);
extern s32 battle_random_process_gives_a_number_between_0_7fff(void);
extern void func_801843EC(s16* p);
extern battle_action_data_t* g_target_current_action;
extern s16 g_current_ability_xa;

void battle_critical_hit_calculation(void) {
    s32 rnd;
    s16* p;
    s16 v;
    if (battle_random_process_and_checks_against_r5(0x64, 4) == 0) {
        g_target_current_action->critical = 1;
        rnd = battle_random_process_gives_a_number_between_0_7fff();
        p = &g_current_ability_xa;
        v = *p;
        *p = v + (rnd * v) / 32768;
        func_801843EC(p);
    }
}
