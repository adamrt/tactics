#include "fft/jobstts.h"

extern void* memset(void* destination, s32 value, u32 size);
extern jobstts_ability_selection_state_t g_jobstts_ability_selection_states[5];

void jobstts_clear_ability_selection_states(void) {
    memset(g_jobstts_ability_selection_states, 0,
        sizeof(g_jobstts_ability_selection_states));
}
