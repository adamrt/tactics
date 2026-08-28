#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;
extern u8 g_ai_decision_state;
extern s32 g_ai_cowardly_movement_step;
extern u8 g_ai_movement_scenario;

extern s32 func_801999C8(void);
extern s32 func_801994F8(battle_ai_unit_decision_t*);
extern void func_8019693C(s32, s32);
extern void func_801993A0(void);

s32 battle_ai_cowardly_movement_routine(void) {
    battle_ai_data_t* ai = &g_ai_data_base;
    s32 state;

    if (g_ai_decision_state == 0) {
        goto reset;
    }
    state = g_ai_cowardly_movement_step;
    if (state == 0) {
        goto step_a;
    }
    if (state == 1) {
        goto step_b;
    }
reset:
    g_ai_movement_scenario = 0;
step_a:
    if (func_801999C8() == -1) {
        g_ai_cowardly_movement_step = 0;
        return -1;
    }
step_b:
    if (func_801994F8(ai->acting_unit_decision) == -1) {
        g_ai_cowardly_movement_step = 1;
        return -1;
    }
    func_8019693C(0xff, 0);
    ai->movement_scenario = 1;
    ai->candidate_coords[1].word = ai->candidate_coords[0].word;
    func_801993A0();
    return 0;
}
